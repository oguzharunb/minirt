#include "camera.h"
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

t_camera	*init_camera(void)
{
	t_camera	*cam;
	t_vec3		look_at;
	t_vec3		world_up;
	double		theta;
	double		h;
	t_vec3		center;

	cam = malloc(sizeof(t_camera));
	if (!cam)
		return (NULL);
	// simdilik sabit
	cam->origin = vec(CAMERA_POS_X, CAMERA_POS_Y, CAMERA_POS_Z);
	look_at = vec(0.0, 0.0, 0.0);
	cam->forward = vec_normalize(vec_sub(look_at, cam->origin));
	world_up = vec(0.0, 1.0, 0.0);
	cam->right = vec_normalize(vec_cross(cam->forward, world_up));
	cam->up = vec_cross(cam->right, cam->forward);
	theta = FOV * M_PI / 180.0;
	h = tan(theta / 2.0);
	cam->viewport_h = 2.0 * h;
	cam->viewport_w = cam->viewport_h * ASPECT_RATIO;
	cam->horizontal = vec_mul(cam->right, cam->viewport_w);
	cam->vertical = vec_mul(cam->up, cam->viewport_h);
	center = vec_add(cam->origin, cam->forward);
	cam->lower_left = vec_sub(vec_sub(center, vec_mul(cam->horizontal, 0.5)),
			vec_mul(cam->vertical, 0.5));
	return (cam);
}
