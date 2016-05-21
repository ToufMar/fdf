#include "fdf.h"

void menu(t_struct *s)
{
	mlx_string_put(s->mlx, s->win, 5, 5, 0xFFFFFF, "___________________________");
	mlx_string_put(s->mlx, s->win, 5, 10, 0xFFFFFF, "___________________________");
	mlx_string_put(s->mlx, s->win, 5, 30, 0xFFFFFF, "|           MENU          |");
	mlx_string_put(s->mlx, s->win, 5, 50, 0xFFFFFF, "| MAP:");
	mlx_string_put(s->mlx, s->win, 70, 50, 0xFFFFFF, s->map_name);
	mlx_string_put(s->mlx, s->win, 265, 50, 0xFFFFFF, "|");
	mlx_string_put(s->mlx, s->win, 5, 70, 0xFFFFFF, "| MOVE : Arrows           |");
	mlx_string_put(s->mlx, s->win, 5, 90, 0xFFFFFF, "| ZOOM : + -              |");
	mlx_string_put(s->mlx, s->win, 5, 110, 0xFFFFFF, "| DEEP : / *              |");
	mlx_string_put(s->mlx, s->win, 5, 130, 0xFFFFFF, "| PROJECTIONS : 1 2       |");
	mlx_string_put(s->mlx, s->win, 5, 150, 0xFFFFFF, "| ROTATION : A S          |");
	mlx_string_put(s->mlx, s->win, 5, 170, 0xFFFFFF, "| EXIT : ESC              |");
	mlx_string_put(s->mlx, s->win, 5, 180, 0xFFFFFF, "___________________________");
	mlx_string_put(s->mlx, s->win, 5, 185, 0xFFFFFF, "___________________________");
}

int ft_key_print(int key, t_struct *s)
{
	(key == 53) ? exit(0) : 0;
	s->yplace += (key == 125) ? 10 : 0;
	s->yplace -= (key == 126) ? 10 : 0;
	s->xplace += (key == 124) ? 10 : 0;
	s->xplace -= (key == 123) ? 10 : 0;
	s->zoom += (key == 69) ? 0.5 : 0;
  if (s->zoom > 1)
   s->zoom -= (key == 78) ? 0.5 : 0;
  s->prof += (key == 67) ? 1 : 0;
  if (s->prof > 1)
  s->prof -= (key == 75) ? 1 : 0;
	s->plat += (key == 0) ? 0.01 : 0;
	s->plat -= (key == 1) ? 0.01 : 0;
	if (key == 83)
		s->para = 1;
	else if (key == 84)
		s->para = 0;
	put_img(s);
	return(1);
}
