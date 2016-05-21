/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroturea <mroturea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 14:28:42 by mroturea          #+#    #+#             */
/*   Updated: 2016/05/21 17:36:36 by mroturea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
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

int	count_col(char **tab, t_struct *s)
{
	int i;
	i = 0;
	while (tab[i])
		i++;
	s->nb_col = i;
	return (i);
}

int		*get_int_tab(char *str, t_struct *s)
{
	int i;
	char **tmp;
	int *tab = NULL;

	i = 0;
	tmp = ft_strsplit(str, ' ');
	tab = (int *)malloc(sizeof(int) * count_col(tmp, s));
	while (tmp[i])
	{
		tab[i] = ft_atoi(tmp[i]);
		if (tab[i] > s->zmax)
			s->zmax = tab[i];
		if (tab[i] < s->zmin)
			s->zmin = tab[i];
		i++;
	}
	return(tab);
}
