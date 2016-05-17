/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroturea <mroturea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 13:35:06 by mroturea          #+#    #+#             */
/*   Updated: 2016/05/17 19:00:04 by mroturea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include "get_next_line.h"
#include <math.h>

int ft_key_print(int keycode, void *param)
{
	param = 0;
	printf("key ievent : %d\n", keycode);
	return(0);
}

t_point	calcul(int x, int y, int z, t_struct *s)
{
	t_point point;

	point.x = s->place + ((sqrt(2.0) / 2.0) * ((x * s->zoom) - (y * s->zoom)));
	point.y = s->place - ((sqrt(2.0 / 3.0) * (z * s->zoom / s->prof)) -
	((1 / sqrt(9.0)) * (s->zoom * (x + y))));
	return (point);
}

void print_map(t_struct *s, t_tab *t)
{
	int x;
	int y;
	t_point p1;
	t_point p2;

	x = -1;
	while (++x < t->nb_col)
	{
		y = -1;
		while (++y < t->nb_line)
		{
			p1 = calcul(x, y, t->tab[y][x], s);
			if (x + 1 < t->nb_col)
			{
				p2 = calcul(x + 1, y, t->tab[y][x + 1], s);
				print_trace(p1, p2, s);
			}
			if (y + 1 < t->nb_line)
			{
				p2 = calcul(x, y + 1, t->tab[y + 1][x], s);
				print_trace(p1, p2, s);
			}
		}
	}
}

void mlx(t_struct *s, t_tab *t)
{
	s->prof = 10;
	s->place = 400;
	s->zoom = 30;
	s->mlx = mlx_init();
	s->win = mlx_new_window(s->mlx, HGT, WDT, "CyberPedo");
	s->mlx_img = mlx_new_image(s->mlx, HGT, WDT);
	s->ptr_img = mlx_get_data_addr(s->mlx_img, &(s->bit_pp), &(s->size_line), &(s->endian));
	init_color(s);
	print_map(s, t);
	mlx_put_image_to_window(s->mlx, s->win, s->mlx_img, 0, 0);
	mlx_key_hook(s->win, ft_key_print, 0);
	mlx_loop(s->mlx);
}

int main(int ac, char **av)
{
	t_struct *s;
	t_tab *t;
	ac = 0;
	char *line;
	int fd;
	int i = 0;

	s = NULL;
	fd = open(av[1], O_RDONLY);
	t = (t_tab *)malloc(sizeof(t_tab));
	t->tab = (int **)malloc(sizeof(int *) * count_line(av[1]));
	s = (t_struct *)malloc(sizeof(t_struct));
	while ((get_next_line(fd, &line)) > 0)
	{
		t->tab[i] = get_int_tab(line, t);
		i++;
	}
	t->nb_line = i;
	t->tab[i] = NULL;
	mlx(s, t);
}
