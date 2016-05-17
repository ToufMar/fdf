/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroturea <mroturea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 14:22:53 by mroturea          #+#    #+#             */
/*   Updated: 2016/05/17 19:00:06 by mroturea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int ft_abs(int nb)
{
		return ((nb < 0) ? -nb : nb);
}

void init_color(t_struct *s)
{
	s->blue = 255;
	s->green = 255;
	s->red = 255;
}

void put_pixel_to_image(t_point p1 , t_struct *s)
{
		if 	(p1.x <= WDT && p1.y <= HGT && p1.x > 0 && p1.y > 0)
		{
			s->ptr_img[(s->size_line * p1.y) + (4 * p1.x) + 2] = s->blue;
			s->ptr_img[(s->size_line * p1.y) + (4 * p1.x) + 1] = s->green;
			s->ptr_img[(s->size_line * p1.y) + (4 * p1.x)] = s->red;
		}
}

void print_trace(t_point p1, t_point p2, t_struct *s)
{
	t_bresen 	point;

	point.dx = ft_abs((p2.x - p1.x));
	point.sx = p1.x < p2.x ? 1 : -1;
	point.dy = ft_abs((p2.y - p1.y));
	point.sy = p1.y < p2.y ? 1 : -1;
	point.err = (point.dx > point.dy ? point.dx : -point.dy) / 2;
	while (!(p1.x == p2.x && p1.y == p2.y))
	{
		put_pixel_to_image(p1, s);
		point.err2 = point.err;
		if (point.err2 > -point.dx)
		{
			point.err -= point.dy;
			p1.x += point.sx;
		}
		if (point.err2 < point.dy)
		{
			point.err += point.dx;
			p1.y += point.sy;
		}
	}
}
