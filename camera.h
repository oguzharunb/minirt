#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define CAMERA_POS_X  12.0
# define CAMERA_POS_Y  -10.0
# define CAMERA_POS_Z  -5.0

# define ASPECT_RATIO  (16.0 / 9.0)
# define FOV           80.0

typedef struct s_camera {
    t_vec3  origin;
    t_vec3  forward;
    t_vec3  right;
    t_vec3  up;

    double  viewport_w;
    double  viewport_h;

    t_vec3  horizontal;
    t_vec3  vertical;
    t_vec3  lower_left;
}   t_camera;

#endif
