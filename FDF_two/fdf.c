#include "fdf.h"
#include <stdio.h>
#include "mlx.h"
#include "get_next_line.h"

int ft_key_print(int keycode, void *param)
{
	param = 0;
	printf("key ievent : %d\n", keycode);
	return(0);
}

void print_trace(int x, int y, int xf, int yf, t_info list)
{
   int dx = xf - x;
   int dy = yf - y;
   int cumul = dx / 2;

   while(x <= xf)
   {
   		cumul += dy;
   		if (cumul >= dx)
   		{
   			cumul -=dx;
   			y+= 1;
  		}
   		mlx_pixel_put(list.mlx, list.win, x, y, 0xFFFFFF);
   		x++;
   }
}

int	count_line(char *av)
{
	int fd;
	char *line;
	int i;
	
	i = 0;
	if ((fd = open(av, O_RDONLY)) > 0)
	{
		while (get_next_line(fd, &line) > 0)
			i++;
		close(fd);
		return (i);
	}
	else
		return (-1);
}

int	count_col(char **tab)
{
	int i;
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		*get_int_tab(char *str)
{
	int i;
	char **tmp;
	int *tab = NULL;
	
	i = 0;
	tmp = ft_strsplit(str, ' ');
	tab = (int *)malloc(sizeof(int) * count_col(tmp));
	while (tmp[i])
	{
		tab[i] = ft_atoi(tmp[i]);
		i++;
	}
	return(tab);
}

int main(int ac, char **av)
{
	//	t_info list;
	ac = 0;
	char *line;
	int **tab;
	int fd;
	int i = 0;
	
	fd = open(av[1], O_RDONLY);
	tab = (int **)malloc(sizeof(int *) * count_line(av[1]) + 1);
	while ((get_next_line(fd, &line)) > 0)
	{
		tab[i] = get_int_tab(line);
		i++;
	}
	tab[i] = NULL;
	/*	list.mlx = mlx_init();
		list.win = mlx_new_window(list.mlx, HGT, WDT, "CyberPedo");
		mlx_key_hook(list.win, ft_key_print, 0);
		print_trace(150, 150, 178, 189, list);
		mlx_loop(list.mlx);*/
}
