/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 04:43:32 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/16 04:13:58 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		pcleanup(char **s)
{
	int		i;

	i = 0;
	if (s)
		while (s[i])
			free(s[i++]);
	free(s);
	return (1);
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
	if (f & VTX_START)
		l->start = l->num_rooms;
	else if (f & VTX_END)
		l->end = l->num_rooms;
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
		if (!(s = ft_split(l->file[l->p], ft_strlen(l->file[l->p]), &i)) ||
																		i != 3)
			return (pcleanup(s));
		if (add_room(l, s, f))
			return (pcleanup(s));
		pcleanup(s);
		l->p++;
	}
	return (!(l->has_start && l->has_end) || !l->num_rooms);
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
