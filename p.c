/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 04:43:32 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/05 05:37:31 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		cleanup(char **s)
{
	int		i;

	i = 0;
	if (s)
		while (s[i])
			free(s[i++]);
	free(s);
	return (1);
}

int		parse_hash(t_lemin *l)
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

int		parse_ants(t_lemin *l)
{
	if (parse_hash(l))
		return (1);
	if (l->file[l->p] == NULL)
		return (1);
	if (ft_natoi(l->file[l->p++], &l->num_ants))
		return (1);
	return (l->num_ants <= 0);
}

int		add_room(t_lemin *l, char **s, int f)
{
	int		x;
	int		y;

	if ((f & VTX_START) && (f & VTX_END))
		return (1);
	if (ft_natoi(s[1], &x) || ft_natoi(s[2], &y))
		return (1);
	if (s[0][0] == 'L' || s[0][0] == '\0')
		return (1);
	*(l->pr) = malloc(sizeof(t_room));
	(*(l->pr))->next = NULL;
	(*(l->pr))->num = l->num_rooms++;
	(*(l->pr))->name = ft_strdup(s[0]);
	(*(l->pr))->x = x;
	(*(l->pr))->y = y;
	(*(l->pr))->f = f;
	l->pr = &(*(l->pr))->next;
	return (0);
}

int		parse_rooms(t_lemin *l)
{
	int		f;
	int		i;
	char	**s;

	while (l->file[l->p])
	{
		f = parse_hash(l);
		if (ft_strchr(l->file[l->p], '-'))
			break ;
		if (l->file[l->p] == NULL)
			break ;
		if (!(s = ft_split(l->file[l->p], ft_strlen(l->file[l->p]), &i)) || i != 3)
			return (cleanup(s));
		if (add_room(l, s, f))
			return (cleanup(s));
		cleanup(s);
		l->p++;
	}
	return (!(l->has_start && l->has_end) || !l->num_rooms);
}

t_room	*find_room(t_room *lst, char *name, int num)
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

int		add_link(t_lemin *l)
{
	char	**s;
	t_room	*a;
	t_room	*b;

	s = ft_strsplit(l->file[l->p], '-');
	if (!ft_strcmp(s[0], s[1]))
		return (cleanup(s));
	if (!(a = find_room(l->rooms, s[0], -1)))
		return (cleanup(s));
	if (!(b = find_room(l->rooms, s[1], -1)))
		return (cleanup(s));
	if (l->adj_mtx[a->num][b->num])
		return (cleanup(s));
	l->adj_mtx[a->num][b->num] = 1;
	l->adj_mtx[b->num][a->num] = 1;
	cleanup(s);
	return (0);
}

int		parse_links(t_lemin *l)
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

void	setup_lemin(t_lemin *l)
{
	int		n;
	int		i;

	n = l->num_rooms;
	l->adj_mtx = malloc(sizeof(int*) * (n + 1));
	i = 0;
	while (i < n)
	{
		l->adj_mtx[i] = malloc(sizeof(int) * n);
		ft_memset(l->adj_mtx[i], 0, sizeof(int) * n);
		i++;
	}
	l->adj_mtx[i] = NULL;
	l->vertices = malloc(sizeof(t_vertex) * n);
	ft_memset(l->vertices, 0, sizeof(t_vertex) * n);
}

int		parse(t_lemin *lemin)
{
	lemin->pr = &lemin->rooms;
	if (parse_ants(lemin))
		return (1);
	if (parse_rooms(lemin))
		return (1);
	setup_lemin(lemin);
	if (parse_links(lemin))
		return (1);
	if (lemin->has_start != 1 || lemin->has_end != 1)
		return (1);
	return (0);
}
