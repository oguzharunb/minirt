#include "camera.h"
#include <stdlib.h>

t_camera	*create_camera(t_point3 *location, t_vec3 *direction, double aspect_ratio, double fov)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->aspect_ratio = aspect_ratio;
	camera->direction = direction;
	camera->fov = fov;
	camera->location = location;
}