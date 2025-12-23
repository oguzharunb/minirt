/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objs_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:07:43 by msengul           #+#    #+#             */
/*   Updated: 2025/12/23 18:20:22 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	sphere_add_back(t_sphere **lst, t_sphere *new)
{
	t_sphere	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	plane_add_back(t_plane **lst, t_plane *new)
{
	t_plane	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	cylinder_add_back(t_cylinder **lst, t_cylinder *new)
{
	t_cylinder	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
