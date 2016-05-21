/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroturea <mroturea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 14:22:53 by mroturea          #+#    #+#             */
/*   Updated: 2016/05/21 18:24:03 by mroturea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void init_color(t_struct *s, int z)
{
	/*bleu*/
	if (z >= 0 && z <= 2)
	{
		s->blue = 51;
		s->green = 153;
		s->red = 255;
	}
	/*jaune*/
	if (z >= 3 && z <= 15)
	{
		s->blue = 255;
		s->green = 204;
		s->red = 0;
	}
	/*vert*/
	if (z >= 16 && z <= 50)
	{
		s->blue = 51;
		s->green = 255;
		s->red = 51;
	}
	/*marron*/
	if (z >= 51 && z <= 75)
	{
		s->blue = 153;
		s->green = 102;
		s->red = 0;
	}
	/*blanc*/
	if (z >= 76 && z <= 90)
	{
		s->blue = 255;
		s->green = 255;
		s->red = 255;
	}
}

void put_pixel_to_image(int x, int y, t_struct *s)
{
		if 	(x < WDT && y < HGT && x > 0 && y > 0)
		{
			s->ptr_img[(s->size_line * y) + (4 * x) + 2] = s->blue;
			s->ptr_img[(s->size_line * y) + (4 * x) + 1] = s->green;
			s->ptr_img[(s->size_line * y) + (4 * x)] = s->red;
		}
}

void print_trace(t_point p1, t_point p2, t_struct *s)
{
	t_bresen 	point;

	point.dx = abs((p2.x - p1.x));
	point.sx = p1.x < p2.x ? 1 : -1;
	point.dy = abs((p2.y - p1.y));
	point.sy = p1.y < p2.y ? 1 : -1;
	point.err = (point.dx > point.dy ? point.dx : -point.dy) / 2;

	while (!(p1.x == p2.x && p1.y == p2.y))
	{

		put_pixel_to_image(p1.x, p1.y, s);
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
