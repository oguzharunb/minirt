/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 00:43:23 by msengul           #+#    #+#             */
/*   Updated: 2025/12/24 00:45:37 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <stdlib.h>

void	free_spheres(t_sphere *sp)
{
	t_sphere	*tmp;

	while (sp)
	{
		tmp = sp->next;
		free(sp);
		sp = tmp;
	}
}

void	free_planes(t_plane *pl)
{
	t_plane	*tmp;

	while (pl)
	{
		tmp = pl->next;
		free(pl);
		pl = tmp;
	}
}

void	free_cylinders(t_cylinder *cy)
{
	t_cylinder	*tmp;

	while (cy)
	{
		tmp = cy->next;
		free(cy);
		cy = tmp;
	}
}
