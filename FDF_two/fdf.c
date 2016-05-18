/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroturea <mroturea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 13:35:06 by mroturea          #+#    #+#             */
/*   Updated: 2016/05/18 17:52:11 by mroturea         ###   ########.fr       */
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

	point.x = s->xplace + ((sqrt(2.0) / 2.0) * ((x * s->zoom) - (y * s->zoom)));
	point.y = s->yplace - ((sqrt(2.0 / 2.0) * (z * s->zoom / s->prof)) -
	((1 / sqrt(6.0)) * (s->zoom * (x + y))));
	return (point);
}

void print_map(t_struct *s, t_tab *t)
{
	int x;
	int y;
	t_point p1;
	t_point p2;

	x = 0;
	y = 0;
	while (y < t->nb_line)
	{
		while (x < t->nb_col)
		{
			p1 = calcul(x, y, t->tab[y][x], s);
			x++;
			init_color(s, t->tab[y][x]);
			if (x < t->nb_col)
			{
				p2 = calcul(x, y, t->tab[y][x], s);
				print_trace(p1, p2, s);
			}
			if (y < t->nb_line - 1)
			{
				p2 = calcul(x - 1, y + 1, t->tab[y + 1][x - 1], s);
				print_trace(p1, p2, s);
			}
		}
		x = 0;
		y++;
	}
}

void mlx(t_struct *s, t_tab *t)
{
	s->prof = 20;
	s->yplace = 200;
	s->xplace = 800;
	s->zoom = 7;
	s->mlx = mlx_init();
	s->win = mlx_new_window(s->mlx, HGT, WDT, "CyberPedo");
	s->mlx_img = mlx_new_image(s->mlx, HGT, WDT);
	s->ptr_img = mlx_get_data_addr(s->mlx_img, &(s->bit_pp), &(s->size_line), &(s->endian));

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
	int u;
	int i = 0;
	printf("ok");
	s = NULL;
	fd = open(av[1], O_RDONLY);
	t = (t_tab *)malloc(sizeof(t_tab));
	u = count_line(av[1]);
	t->tab = (int **)malloc(sizeof(int *) * u);
	s = (t_struct *)malloc(sizeof(t_struct));
	ft_memset(s, 0, sizeof(s));
	while ((get_next_line(fd, &line)) > 0)
	{
				t->tab[i] = get_int_tab(line, t);
				i++;
	}
	t->nb_line = i;
	t->tab[i] = NULL;
	mlx(s, t);
}
