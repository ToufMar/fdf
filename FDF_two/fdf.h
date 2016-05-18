/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroturea <mroturea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 14:21:54 by mroturea          #+#    #+#             */
/*   Updated: 2016/05/18 17:51:19 by mroturea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
#include "libft/libft.h"
#include <mlx.h>
# define HGT 2048
# define WDT 2080


typedef struct	s_struct
{
	void *mlx;
	void *win;
	void *mlx_img;
	char *ptr_img;
	int	 bit_pp;
	int size_line;
	int endian;
	int red;
	int blue;
	int green;
	int prof;
	int yplace;
	int xplace;
	int zoom;
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

typedef struct s_tab
{
	int nb_col;
	int nb_line;
	int **tab;
}							t_tab;

typedef struct s_point
{
	int x;
	int y;
}							t_point;

int ft_key_print(int keycode, void *param);
void init_color(t_struct *s, int z);
void put_pixel_to_image(int x, int y, t_struct *s);
void print_trace(t_point p1, t_point p2, t_struct *s);
int ft_abs(int nb);
int	count_line(char *av);
int	count_col(char **tab, t_tab *t);
int		*get_int_tab(char *str, t_tab *t);
#endif
