#include "objects.h"
#include "minirt.h"
#include <stdlib.h>
#include <math.h>

int hit_disk(t_ray *ray, t_vec3 center, t_vec3 normal, double radius, double *t)
{
    double  denom;
    double  num;
    double  t_temp;
    t_vec3  p;
    t_vec3  v;

    denom = vec_dot(ray->direction, normal);
    if (fabs(denom) < 1e-6) 
        return (0);
    t_vec3 oc = vec_sub(center, ray->origin);
    num = vec_dot(oc, normal);
    t_temp = num / denom;
    if (t_temp < 1e-4)
        return (0);
    p = vec_add(ray->origin, vec_mul(ray->direction, t_temp));
    v = vec_sub(p, center);
    if (vec_dot(v, v) <= radius * radius)
    {
        *t = t_temp;
        return (1);
    }
    return (0);
}

int hit_cylinder(t_cylinder *cy, t_ray *ray, double *t)
{
    double  t_body = -1.0;
    double  t_top = -1.0;
    double  t_bottom = -1.0;
    int     hit_any = 0;
    
    t_vec3  oc = vec_sub(ray->origin, cy->center);
    double  dot_r_axis = vec_dot(ray->direction, cy->axis);
    double  dot_oc_axis = vec_dot(oc, cy->axis);
    double  a = vec_dot(ray->direction, ray->direction) - (dot_r_axis * dot_r_axis);
    double  b = 2 * (vec_dot(ray->direction, oc) - (dot_r_axis * dot_oc_axis));
    double  c = vec_dot(oc, oc) - (dot_oc_axis * dot_oc_axis) - (cy->radius * cy->radius);
    double  discriminant = b * b - 4 * a * c;

    if (discriminant >= 0)
    {
        double t1 = (-b - sqrt(discriminant)) / (2 * a);
        double t2 = (-b + sqrt(discriminant)) / (2 * a);
        double m;

        if (t1 > 1e-4)
        {
            m = dot_r_axis * t1 + dot_oc_axis;
            if (m >= -cy->height / 2.0 && m <= cy->height / 2.0)
            {
                t_body = t1;
                hit_any = 1;
            }
        }
        if (t_body == -1.0 && t2 > 1e-4)
        {
            m = dot_r_axis * t2 + dot_oc_axis;
            if (m >= -cy->height / 2.0 && m <= cy->height / 2.0)
            {
                t_body = t2;
                hit_any = 1;
            }
        }
    }
    t_vec3 top_center = vec_add(cy->center, vec_mul(cy->axis, cy->height / 2.0));
    if (hit_disk(ray, top_center, cy->axis, cy->radius, &t_top))
        hit_any = 1;
    t_vec3 bot_center = vec_sub(cy->center, vec_mul(cy->axis, cy->height / 2.0));
    t_vec3 bot_axis = vec_mul(cy->axis, -1.0); 
    if (hit_disk(ray, bot_center, bot_axis, cy->radius, &t_bottom))
        hit_any = 1;
    if (!hit_any)
        return (0);
    double min_t = 1e30; 
    int found = 0;

    if (t_body > 1e-4 && t_body < min_t) { min_t = t_body; found = 1; }
    if (t_top > 1e-4 && t_top < min_t)   { min_t = t_top; found = 1; }
    if (t_bottom > 1e-4 && t_bottom < min_t) { min_t = t_bottom; found = 1; }

    if (found)
    {
        *t = min_t;
        return (1);
    }
    
    return (0);
}