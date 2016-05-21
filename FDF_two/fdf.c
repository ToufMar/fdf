/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroturea <mroturea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 13:35:06 by mroturea          #+#    #+#             */
/*   Updated: 2016/05/21 18:24:03 by mroturea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"




void put_img(t_struct *s)
{

	s->mlx_img = mlx_new_image(s->mlx, HGT, WDT);
	s->ptr_img = mlx_get_data_addr(s->mlx_img, &(s->bit_pp), &(s->size_line), &(s->endian));
	if (s->para == 1)
		print_map_iso(s);
	else if (!s->para)
		print_map_para(s);
	mlx_put_image_to_window(s->mlx, s->win, s->mlx_img, 0, 0);
	printf("%d\n", s->prof);
	menu(s);
	mlx_destroy_image(s->mlx, s->ptr_img);
}

void mlx(t_struct *s)
{
	s->prof = 25;
	s->yplace = 100;
	s->xplace = 100;
	s->zoom = 20.0;
	if (s->para == 1)
		s->plat = 2.0;
	else
		s->plat = 0.35;
	s->mlx = mlx_init();
	s->win = mlx_new_window(s->mlx, HGT, WDT, "CyberPedo");
	put_img(s);
	mlx_hook(s->win, 2, 3, ft_key_print, s);
	mlx_loop(s->mlx);
}



int main(int ac, char **av)
{
	t_struct *s;
	ac = 0;
	char *line;
	int fd;
	int u;
	int i = 0;

	s = NULL;
	fd = open(av[1], O_RDONLY);
	u = count_line(av[1]);
	s = (t_struct *)malloc(sizeof(t_struct));
	s->tab = (int **)malloc(sizeof(int *) * u);
	ft_memset(s, 0, sizeof(s));
	s->zmin = 0;
	s->zmax = 0;
	while ((get_next_line(fd, &line)) > 0)
	{
				s->tab[i] = get_int_tab(line, s);
				i++;
	}
	s->nb_line = i;
	s->tab[i] = NULL;
	s->para = 0;
	s->map_name = av[1];
	mlx(s);
}
