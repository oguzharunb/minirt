#include "objects.h"
#include "camera.h"
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include "parser.h"

static void free_split(char **split)
{
    int i = 0;
    if (!split) return;
    while (split[i])
        free(split[i++]);
    free(split);
}

static t_rgb parse_rgb(char *str, t_scene *scene)
{
    char    **split;
    t_rgb   color;
    int     r, g, b;

    split = ft_split(str, ',');
    if (!split[0] || !split[1] || !split[2])
    {
        free_split(split);
        exit_error("Invalid color format (R,G,B)", scene);
    }
    r = ft_atoi(split[0]);
    g = ft_atoi(split[1]);
    b = ft_atoi(split[2]);
    free_split(split);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        exit_error("Color values must be between 0-255", scene);

    color.r = r;
    color.g = g;
    color.b = b;
    return (color);
}

void init_scene(t_scene *scene)
{
    scene->spheres = NULL;
    scene->planes = NULL;
    scene->cylinders = NULL;
    scene->amb.ratio = -1.0; 
    scene->light.ratio = -1.0;
}

static void setup_camera(t_camera *cam, double fov_degrees)
{
    t_vec3  global_up;
    double  theta;
    double  h;
    double  viewport_height;
    double  viewport_width;

    cam->forward = vec_normalize(cam->forward);
    theta = fov_degrees * M_PI / 180.0;
    h = tan(theta / 2.0);
    viewport_height = 2.0 * h;
    viewport_width = ASPECT_RATIO * viewport_height;

    cam->viewport_h = viewport_height;
    cam->viewport_w = viewport_width;

    global_up = vec(0, 1, 0);
    if (fabs(cam->forward.y) > 0.999) 
        cam->right = vec_normalize(vec_cross(vec(0, 0, 1), cam->forward));
    else
        cam->right = vec_normalize(vec_cross(global_up, cam->forward));

    cam->up = vec_cross(cam->forward, cam->right);
    cam->horizontal = vec_mul(cam->right, viewport_width);
    cam->vertical = vec_mul(cam->up, viewport_height);

    cam->lower_left = vec_sub(cam->origin, vec_mul(cam->horizontal, 0.5));
    cam->lower_left = vec_sub(cam->lower_left, vec_mul(cam->vertical, 0.5));
    cam->lower_left = vec_add(cam->lower_left, cam->forward); 
}

void parse_ambient(char *line, t_scene *scene)
{
    char    **split;

    if (scene->amb.ratio != -1.0) // Daha önce atanmış mı kontrolü
        exit_error("Multiple Ambient Light defined", scene);
    
    split = ft_split(line, ' ');
    if (!split[1] || !split[2])
    {
        free_split(split);
        exit_error("Missing Ambient parameters", scene);
    }
    
    scene->amb.ratio = ft_atof(split[1]);
    scene->amb.color = parse_rgb(split[2], scene);
    
    if (scene->amb.ratio < 0.0 || scene->amb.ratio > 1.0)
        exit_error("Ambient ratio must be in range [0.0, 1.0]", scene);

    free_split(split);
}

void parse_camera(char *line, t_scene *scene)
{
    char    **split;
    double  fov_deg;
    
    split = ft_split(line, ' ');
    if (!split[1] || !split[2] || !split[3])
    {
        free_split(split);
        exit_error("Missing Camera parameters", scene);
    }

    scene->camera.origin = parse_vec3(split[1]);
    scene->camera.forward = parse_vec3(split[2]);
    fov_deg = ft_atof(split[3]);

    if (fov_deg < 0 || fov_deg > 180)
        exit_error("Camera FOV must be in range [0, 180]", scene);
    if (vec_length(scene->camera.forward) == 0)
        exit_error("Camera orientation cannot be zero vector", scene);

    setup_camera(&scene->camera, fov_deg);
    free_split(split);
}

void parse_light(char *line, t_scene *scene)
{
    char    **split;

    if (scene->light.ratio != -1.0)
        exit_error("Multiple Lights defined", scene);

    split = ft_split(line, ' ');
    if (!split[1] || !split[2] || !split[3])
    {
        free_split(split);
        exit_error("Missing Light parameters", scene);
    }

    scene->light.position = parse_vec3(split[1]);
    scene->light.ratio = ft_atof(split[2]);
    scene->light.color = parse_rgb(split[3], scene);

    if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
        exit_error("Light ratio must be in range [0.0, 1.0]", scene);

    free_split(split);
}

void parse_sphere(char *line, t_scene *scene)
{
    t_sphere *new_sp = malloc(sizeof(t_sphere));
    if (!new_sp) exit_error("Malloc error", scene);
    
    char **split = ft_split(line, ' ');
    if (!split[1] || !split[2] || !split[3])
    {
        free(new_sp);
        free_split(split);
        exit_error("Missing Sphere parameters", scene);
    }
    
    new_sp->center = parse_vec3(split[1]);
    new_sp->radius = ft_atof(split[2]) / 2.0;
    new_sp->color = parse_rgb(split[3], scene);
    new_sp->next = NULL;

    if (!scene->spheres) 
        scene->spheres = new_sp;
    else {
        t_sphere *tmp = scene->spheres;
        while (tmp->next) tmp = tmp->next;
        tmp->next = new_sp;
    }
    free_split(split);
}

void parse_plane(char *line, t_scene *scene)
{
    t_plane     *new_pl = malloc(sizeof(t_plane));
    if (!new_pl) exit_error("Malloc error", scene);

    char **split = ft_split(line, ' ');
    if (!split[1] || !split[2] || !split[3])
    {
        free(new_pl);
        free_split(split);
        exit_error("Missing Plane parameters", scene);
    }
    
    new_pl->point = parse_vec3(split[1]);
    new_pl->normal = parse_vec3(split[2]);
    new_pl->color = parse_rgb(split[3], scene);
    new_pl->next = NULL;
    new_pl->normal = vec_normalize(new_pl->normal);

    if (!scene->planes)
        scene->planes = new_pl;
    else
    {
        t_plane *tmp = scene->planes;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_pl;
    }
    free_split(split);
}

void parse_cylinder(char *line, t_scene *scene)
{
    t_cylinder  *new_cy = malloc(sizeof(t_cylinder));
    if (!new_cy) exit_error("Malloc error", scene);

    char **split = ft_split(line, ' ');
    if (!split[1] || !split[2] || !split[3] || !split[4] || !split[5])
    {
        free(new_cy);
        free_split(split);
        exit_error("Missing Cylinder parameters", scene);
    }
    
    new_cy->center = parse_vec3(split[1]);
    new_cy->axis = parse_vec3(split[2]);
    new_cy->radius = ft_atof(split[3]) / 2.0;
    new_cy->height = ft_atof(split[4]);
    new_cy->color = parse_rgb(split[5], scene);
    new_cy->next = NULL;

    new_cy->axis = vec_normalize(new_cy->axis);

    if (!scene->cylinders)
        scene->cylinders = new_cy;
    else
    {
        t_cylinder *tmp = scene->cylinders;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_cy;
    }
    free_split(split);
}

int is_string_digit(char *str)
{
    int point_check = 0;
    int i = 0;
    while (str[i])
    {
        if (i == 0 && str[i] == '-')
        {
            i++;
            continue;
        }
        else if (point_check == 1 && str[i] == '.')
            return (0);
        else if (point_check == 0 && str[i] == '.')
            point_check = 1;
        else if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void parse_line(char *line, t_scene *scene)
{
    int i = 0;
    int j = 0;
    while (line[j])
    {
        if (line[j] == '\t') line[j] = ' ';
        j++;
    }
    
    char **split = ft_split(line, ' ');
    int k = 0; while(split[k]) free(split[k++]); free(split);

    i = skip_whitespace(line, i);
    
    if (!line[i] || line[i] == '#') return;
    
    if (line[i] == 'A' && line[i + 1] == ' ')
        parse_ambient(line + i, scene);
    else if (line[i] == 'C' && line[i + 1] == ' ')
        parse_camera(line + i, scene);
    else if (line[i] == 'L' && line[i + 1] == ' ')
        parse_light(line + i, scene);
    else if (line[i] == 's' && line[i + 1] == 'p' && line[i + 2] == ' ')
        parse_sphere(line + i, scene);
    else if (line[i] == 'p' && line[i + 1] == 'l' && line[i + 2] == ' ')
        parse_plane(line + i, scene);
    else if (line[i] == 'c' && line[i + 1] == 'y' && line[i + 2] == ' ')
        parse_cylinder(line + i, scene);
    else
        exit_error("Unknown identifier in .rt file", scene);
}

void read_rt_file(char *filename, t_scene *scene)
{
    int     fd;
    char    *line;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        exit_error("Cannot open file", scene);
    
    init_scene(scene);
    
    while ((line = get_next_line(fd)))
    {
        parse_line(line, scene);
        free(line);
    }
    close(fd);
    if (scene->amb.ratio == -1.0)
        exit_error("Missing Ambient Light (A)", scene);
    if (scene->light.ratio == -1.0)
        exit_error("Missing Light (L)", scene);
}

void write_rt_file(t_scene *scene)
{
    printf("--- SCENE DATA ---\n");
    printf("Ambient: Ratio %.2f | Color: %d,%d,%d\n", 
           scene->amb.ratio, scene->amb.color.r, scene->amb.color.g, scene->amb.color.b);
    
    printf("Camera : Origin %.2f,%.2f,%.2f | Forward %.2f,%.2f,%.2f\n",
        scene->camera.origin.x, scene->camera.origin.y, scene->camera.origin.z,
        scene->camera.forward.x, scene->camera.forward.y, scene->camera.forward.z);

    printf("Light  : Pos %.2f,%.2f,%.2f | Ratio %.2f | Color %d,%d,%d\n",
        scene->light.position.x, scene->light.position.y, scene->light.position.z,
        scene->light.ratio, scene->light.color.r, scene->light.color.g, scene->light.color.b);

    t_sphere *s = scene->spheres;
    while (s)
    {
        printf("Sphere : Center %.2f,%.2f,%.2f | Radius %.2f | Color %d,%d,%d\n",
            s->center.x, s->center.y, s->center.z, s->radius, 
            s->color.r, s->color.g, s->color.b);
        s = s->next;
    }
    printf("--- END SCENE ---\n");
}
