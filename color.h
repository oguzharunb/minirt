/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:32:33 by msengul           #+#    #+#             */
/*   Updated: 2025/12/23 16:32:54 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef unsigned int	t_color;

unsigned int			get_prim_color(t_color color, char variant);
void					set_prim_color(t_color *color, unsigned int prim_color,
							char variant);

#endif