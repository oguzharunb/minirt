#include "parser.h"
#include "objects.h"
#include <stdio.h>
#include <stdlib.h>

static void free_tokens(char **tokens)
{
    int i = 0;
    if (!tokens)
        return;
    while (tokens[i])
        free(tokens[i++]);
    free(tokens);
}

double ft_atof(char *str)
{
    double  res;
    double  factor;
    int     sign;
    int     i;

    res = 0.0;
    factor = 1.0;
    sign = 1;
    i = 0;
    if (!str)
        return (0.0);
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
        res = res * 10 + (str[i++] - '0');
    if (str[i] == '.')
    {
        i++;
        while (str[i] >= '0' && str[i] <= '9')
        {
            res = res * 10 + (str[i++] - '0');
            factor *= 10.0;
        }
    }
    return (res / factor * sign);
}

t_vec3 parse_vec3(char *str)
{
    t_vec3  vec;
    char    **tokens;

    tokens = ft_split(str, ',');
    if (!tokens || !tokens[0] || !tokens[1] || !tokens[2])
    {
        free_tokens(tokens);
        printf("Error\nInvalid vector format\n");
        exit(1);
    }
    vec.x = ft_atof(tokens[0]);
    vec.y = ft_atof(tokens[1]);
    vec.z = ft_atof(tokens[2]);
    
    free_tokens(tokens);
    return (vec);
}

// GÜNCELLENEN KISIM: t_rgb döndürüyor
t_rgb parse_color(char *str)
{
    t_rgb   color;
    char    **tokens;
    int     r, g, b;

    tokens = ft_split(str, ',');
    if (!tokens || !tokens[0] || !tokens[1] || !tokens[2])
    {
        free_tokens(tokens);
        printf("Error\nInvalid color format\n");
        exit(1);
    }
    
    r = ft_atoi(tokens[0]);
    g = ft_atoi(tokens[1]);
    b = ft_atoi(tokens[2]);

    free_tokens(tokens);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        printf("Error\nColor values must be in [0-255]\n");
        exit(1);
    }
    color.r = r;
    color.g = g;
    color.b = b;

    return (color);
}

void exit_error(char *msg, t_scene *scene)
{
    (void)scene;
    printf("Error\n%s\n", msg);
    exit(1);
}

int skip_whitespace(char *line, int i)
{
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' || line[i] == '\r'))
        i++;
    return (i);
}