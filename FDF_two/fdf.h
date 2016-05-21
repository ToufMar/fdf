/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroturea <mroturea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 14:21:54 by mroturea          #+#    #+#             */
/*   Updated: 2016/05/21 18:24:05 by mroturea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
#include "libft/libft.h"
#include <mlx.h>
# define HGT 1000
# define WDT 1000
#include <stdio.h>
#include "get_next_line.h"
#include <math.h>

typedef struct	s_struct
{
	void *mlx;
	void *win;
	void *mlx_img;
	char *ptr_img;
	int	 bit_pp;
	int size_line;
	int endian;
	float red;
	float blue;
	float green;
	int prof;
	int yplace;
	int xplace;
	float zoom;
	int para;
	char *map_name;
	int nb_col;
	int nb_line;
	int **tab;
	float plat;
	int zmin;
	int zmax;
	int x;
	int y;
}				t_struct;

typedef struct s_bresen
{
	int dx;
	int sx;
	int dy;
	int sy;
	int err;
	int err2;
}								t_bresen;

typedef struct s_point
{
	int x;
	int y;
}							t_point;

int ft_key_print(int key, t_struct *s);
void init_color(t_struct *s, int z);
void put_pixel_to_image(int x, int y, t_struct *s);
void print_trace(t_point p1, t_point p2, t_struct *s);
int ft_abs(int nb);
int	count_line(char *av);
int	count_col(char **tab, t_struct *s);
int		*get_int_tab(char *str, t_struct *s);
t_point	calcul_iso(int x, int y, int z, t_struct *s);
t_point calcul_para(int y, int x, int z, t_struct *s);
void print_map_iso(t_struct *s);
void create_color(int z, t_struct *s);
void put_img(t_struct *s);
void print_map_para(t_struct *s);
void menu(t_struct *s);
#endif
