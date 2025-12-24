/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msengul <msengul@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:32:17 by msengul           #+#    #+#             */
/*   Updated: 2025/12/23 18:26:33 by msengul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

// 0000000
// 64 bit
// first 32bit

// variant: r for red, g for green, b for blue, t for transparency
unsigned int	get_prim_color(t_color color, char variant)
{
	int	coef;

	coef = 030;
	if (variant == 'g')
		coef -= 010;
	else if (variant == 'b')
		coef -= 020;
	else if (variant == 't')
		coef -= 030;
	color = (color << (030 - coef)) >> 030;
	return (color);
}

// variant: r for red, g for green, b for blue, t for transparency
void	set_prim_color(t_color *color, unsigned int prim_color, char variant)
{
	int	mask;
	int	coef;

	coef = 030;
	mask = 0x00ffffff;
	if (variant == 'g')
	{
		coef = 020;
		mask = 0xff00ffff;
	}
	else if (variant == 'b')
	{
		coef = 010;
		mask = 0xffff00ff;
	}
	else if (variant == 't')
	{
		coef = 00;
		mask = 0xffffff00;
	}
	prim_color = prim_color << coef;
	*color = (*color) & mask;
	*color = (*color) | prim_color;
}
