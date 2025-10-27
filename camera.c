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
	return (camera);
}

t_camera	*init_camera()
{
	t_vec3		*direction;
	t_point3	*location;
	t_camera	*camera;

	direction = create_vector(CAMERA_DIR_X, CAMERA_DIR_Y, CAMERA_DIR_Z);
	if (!direction)
		return (NULL);
	location = create_vector(CAMERA_POS_X, CAMERA_POS_Y, CAMERA_POS_Z);
	if (!location)
		return (free(direction), NULL);
	camera = create_camera(location, direction, ASPECT_RATIO, FOV);
	return (camera);
}