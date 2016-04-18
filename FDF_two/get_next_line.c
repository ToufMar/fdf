/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rberthie <rberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/10 16:25:34 by rberthie          #+#    #+#             */
/*   Updated: 2016/04/15 17:46:08 by rberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	t_list		*find_create_node(t_list **begin, int fd)
{
	t_list			*tmp;

	tmp = *begin;
	if (tmp)
	{
		while (tmp)
		{
			if (fd == (int)tmp->content_size)
				return (tmp);
			tmp = tmp->next;
		}
	}
	if (!(tmp = ft_lstnew("\0", 1)))
		return (NULL);
	tmp->content_size = fd;
	ft_lstadd(begin, tmp);
	return (tmp);
}
/*
static	void		del_list(t_list *liste)
{
    t_list tmp = (*liste);
    t_list next;

    if (liste == NULL) 
    	return;
    while(tmp != NULL)
    {
        if (tmp->content != NULL)
        {
            free(tmp->content);
//          tmp->val = NULL;
        }
        if (tmp->content_size != NULL)
        {
        	free(tmp->content_size);
        }
        next = tmp->nxt;
        free(tmp);
        tmp = next;
    }
    (*liste) = NULL;
}
*/
static	char		*ft_strnjoin_nfree(char *str, char *buff, size_t *i)
{
	char			*tmp;

	tmp = str;
	if (!(str = ft_strnjoin(str, buff, *i)))
		return (NULL);
	ft_memdel((void **)&tmp);
	return (str);
}

int					get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	t_list			*begin;
	size_t			i;
	static	t_list	*file = NULL;

	if (fd < 0 || !line || BUFF_SIZE < 1 || read(fd, buff, 0) < 0)
		ERROR;
	begin = file;
	file = find_create_node(&begin, fd);
	while ((i = M_READ) && (!(ft_strchr(LST_CNT, (EOL || 0x00)))))
		LST_CNT = ft_strnjoin_nfree(LST_CNT, buff, &i);
	i = 0;
	while (((char *)LST_CNT)[i] && ((char *)LST_CNT)[i] != EOL)
		i++;
	if (!(*line = ft_strndup((char *)LST_CNT, i)))
		ERROR;
	if (((char *)LST_CNT)[i] == EOL)
		i++;
	tmp = LST_CNT;
	LST_CNT = ft_strdup(LST_CNT + i);
	ft_memdel((void **)&tmp);
	file = begin;
	if (i)
		return (1);
	return (0);
}
