/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 03:18:46 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/16 03:34:51 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				parse_hash(t_lemin *l)
{
	int		f;

	f = 0;
	while (l->file[l->p])
	{
		if (l->file[l->p][0] != '#')
			break ;
		if (!ft_strcmp(l->file[l->p], "##start"))
		{
			l->has_start++;
			f |= VTX_START;
		}
		else if (!ft_strcmp(l->file[l->p], "##end"))
		{
			l->has_end++;
			f |= VTX_END;
		}
		l->p++;
	}
	return (f);
}

int				parse_ants(t_lemin *l)
{
	if (parse_hash(l))
		return (1);
	if (l->file[l->p] == NULL)
		return (1);
	if (ft_natoi(l->file[l->p++], &l->num_ants))
		return (1);
	return (l->num_ants <= 0);
}

static t_room	*find_room(t_room *lst, char *name, int num)
{
	while (lst)
	{
		if (name && !ft_strcmp(name, lst->name))
			return (lst);
		else if (lst->num == num)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

static int		add_link(t_lemin *l)
{
	char	**s;
	t_room	*a;
	t_room	*b;

	s = ft_strsplit(l->file[l->p], '-');
	if (!ft_strcmp(s[0], s[1]))
		return (pcleanup(s));
	if (!(a = find_room(l->rooms, s[0], -1)))
		return (pcleanup(s));
	if (!(b = find_room(l->rooms, s[1], -1)))
		return (pcleanup(s));
	if (l->adj_mtx[a->num][b->num])
		return (pcleanup(s));
	l->adj_mtx[a->num][b->num] = 1;
	l->adj_mtx[b->num][a->num] = 1;
	pcleanup(s);
	return (0);
}

int				parse_links(t_lemin *l)
{
	char	*s;

	while (l->file[l->p])
	{
		if (parse_hash(l))
			return (1);
		if (l->file[l->p] == NULL)
			break ;
		if ((s = ft_strchr(l->file[l->p], '-')) && !ft_strchr(s + 1, '-'))
		{
			if (add_link(l))
				return (1);
		}
		else
			return (1);
		l->p++;
	}
	return (0);
}
