#include "fdf.h"

t_point	calcul_iso(int x, int y, int z, t_struct *s)
{
	t_point point;

	point.x = s->xplace + ((sqrt(2.0) / 2.0) * ((x * s->zoom) - (y * s->zoom)));
	point.y = s->yplace - ((sqrt(2.0 / 2.0) * (z * s->zoom / s->prof)) -
	((s->plat / sqrt(9.0)) * (s->zoom * (x + y))));
	return (point);
}

t_point 		calcul_para(int x, int y, int z, t_struct *s)
{
	t_point		point;

	point.x = s->xplace + ((x * s->zoom) + s->plat * (y * s->zoom));
	point.y = s->yplace -\
				((z * s->zoom / s->prof) - s->plat * (y * s->zoom));
	return (point);
}

void print_map_iso(t_struct *s)
{
	t_point p1;
	t_point p2;

	s->x = 0;
	s->y = 0;
	while (s->y < s->nb_line)
	{
		while (s->x < s->nb_col)
		{
			p1 = calcul_iso(s->x, s->y, s->tab[s->y][s->x], s);
			s->x++;
	init_color(s, s->tab[s->y][s->x]);
			if (s->x < s->nb_col)
			{
				p2 = calcul_iso(s->x, s->y, s->tab[s->y][s->x], s);
				print_trace(p1, p2, s);
			}
			if (s->y < s->nb_line - 1)
			{
				p2 = calcul_iso(s->x - 1, s->y + 1, s->tab[s->y + 1][s->x - 1], s);
				print_trace(p1, p2, s);
			}
		}
		s->x = 0;
		s->y++;
	}
}

void print_map_para(t_struct *s)
{
	int x;
	int y;
	t_point p1;
	t_point p2;

	x = 0;
	y = 0;
	while (y < s->nb_line)
	{
		while (x < s->nb_col)
		{
			p1 = calcul_para(x, y, s->tab[y][x], s);
			x++;
			init_color(s, s->tab[y][x]);
			if (x < s->nb_col)
			{
				p2 = calcul_para(x, y, s->tab[y][x], s);
				print_trace(p1, p2, s);
			}
			if (y < s->nb_line - 1)
			{
				p2 = calcul_para(x - 1, y + 1, s->tab[y + 1][x - 1], s);
				print_trace(p1, p2, s);
			}
		}
		x = 0;
		y++;
	}
}
