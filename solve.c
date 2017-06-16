/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 14:38:57 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/16 04:17:41 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	fill_vertices(t_lemin *l)
{
	int		i;
	t_room	*cur;

	i = 0;
	cur = l->rooms;
	while (i < l->num_rooms)
	{
		l->vertices[i].n = cur->num;
		l->vertices[i].name = ft_strdup(cur->name);
		l->vertices[i].x = cur->x;
		l->vertices[i].y = cur->y;
		l->vertices[i].attr = cur->f;
		cur = cur->next;
		i++;
	}
}

static void	copy_matrix(int **matrix, int **source, int n)
{
	int		i;
	int		j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			matrix[i][j] = source[i][j];
			j++;
		}
		i++;
	}
}

int			scrub_path(t_lemin *l)
{
	l->graph = create_graph(l->num_rooms);
	copy_matrix(l->graph->matrix, l->adj_mtx, l->num_rooms);
	dfs(l->graph, l->start, l->end);
	if (!l->graph->shortest)
		return (1);
	set_ants(l, l->graph);
	fill_vertices(l);
	return (0);
}
