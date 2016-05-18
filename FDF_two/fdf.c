/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroturea <mroturea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 13:35:06 by mroturea          #+#    #+#             */
/*   Updated: 2016/05/18 19:56:10 by mroturea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include "get_next_line.h"
#include <math.h>



t_point	calcul_iso(int x, int y, int z, t_struct *s)
{
	t_point point;

	point.x = s->xplace + ((sqrt(2) / 2) * ((x * s->zoom) - (y * s->zoom)));
	point.y = s->yplace - ((sqrt(2 / 2) * (z * s->zoom / s->prof)) -
	((1 / sqrt(6)) * (s->zoom * (x + y))));
	return (point);
}

t_point 		calcul_para(int y, int x, int z, t_struct *s)
{
	t_point		point;

	point.x = ((1.3 * x) - (0.1 * (z + s->prof))) * s->zoom + s->xplace;
	point.y = ((1.2 * y) - (0.1 * (z + s->prof))) * s->zoom + s->yplace;
	return (point);
}

void print_map_iso(t_struct *s, t_tab *t)
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
			p1 = calcul_iso(x, y, t->tab[y][x], s);
			x++;
			init_color(s, t->tab[y][x], t->tab[y][x+ 1]);
			if (x < t->nb_col)
			{
				p2 = calcul_iso(x, y, t->tab[y][x], s);
				print_trace(p1, p2, s);
			}
			if (y < t->nb_line - 1)
			{
				p2 = calcul_iso(x - 1, y + 1, t->tab[y + 1][x - 1], s);
				print_trace(p1, p2, s);
			}
		}
		x = 0;
		y++;
	}
}

void print_map_para(t_struct *s, t_tab *t)
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
			p1 = calcul_para(x, y, t->tab[y][x], s);
			x++;
	//		init_color(s, t->tab[y][x]);
			if (x < t->nb_col)
			{
				p2 = calcul_para(x, y, t->tab[y][x], s);
				print_trace(p1, p2, s);
			}
			if (y < t->nb_line - 1)
			{
				p2 = calcul_para(x - 1, y + 1, t->tab[y + 1][x - 1], s);
				print_trace(p1, p2, s);
			}
		}
		x = 0;
		y++;
	}
}

void put_img(t_struct *s, t_tab *t)
{
	s->mlx_img = mlx_new_image(s->mlx, HGT, WDT);
	s->ptr_img = mlx_get_data_addr(s->mlx_img, &(s->bit_pp), &(s->size_line), &(s->endian));
	if (s->para == 1)
		print_map_iso(s, t);
	else if (!s->para)
		print_map_para(s, t);
	mlx_put_image_to_window(s->mlx, s->win, s->mlx_img, 0, 0);
	mlx_destroy_image(s->mlx, s->ptr_img);
}

void mlx(t_struct *s, t_tab *t)
{
	s->prof = 25;
	s->yplace = 100;
	s->xplace = 1000;
	s->zoom = 40;
	s->mlx = mlx_init();
	s->win = mlx_new_window(s->mlx, HGT, WDT, "CyberPedo");
	put_img(s, t);
	mlx_hook(s->win, 2, 3, ft_key_print, s);
	mlx_loop(s->mlx);
}

int ft_key_print(int key, t_struct *s, t_tab *t)
{
	if (key == 126)
		s->yplace += 10;
	else if (key == 125)
		s->yplace -= 10;
	else if (key == 123)
		s->xplace += 10;
	else if (key == 124)
		s->xplace -= 10;
	else if (key == 53)
		exit(0);
	else if (key == 69)
		s->zoom += 10;
	else if (key == 78)
		s->zoom -= 10;
	else if (key == 67)
		s->prof += 10;
	else if (key == 75)
		s->prof -= 10;
	put_img(s, t);
	return(1);
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
	if (ft_strcmp(av[2], "para"))
		s->para = 1;
	else if (ft_strcmp(av[2], "iso"))
		s->para = 0;
	mlx(s, t);
}
