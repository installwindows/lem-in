/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 14:38:57 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/09 06:52:26 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	set_ants(t_lemin *l, t_graph *g)
{
	int		i;

	l->ants = malloc(sizeof(t_ant) * l->num_ants);
	i = 0;
	while (i < l->num_ants)
	{
		l->ants[i].num = i + 1;
		l->ants[i].pos = 0;
		l->ants[i].done = 0;
		l->ants[i].path = g->shortest;
		l->ants[i].size = g->size;
		l->ants[i].moved = 0;
		i++;
	}
}

void	move_ants(t_lemin *l)
{
	int		i;
	int		j;
	int		n;
	int		c;

	i = 0;
	c = 1;
	while (c)
	{
		c = 0;
		j = 0;
		n = 0;
		while (j < l->num_ants)
		{
			if (!l->ants[j].done)
			{
				if (l->vertices[l->ants[j].path[l->ants[j].pos + 1]].attr & VTX_END)
				{
					c = 1;
					l->ants[j].done = 1;
					l->ants[j].moved = 1;
					l->vertices[l->ants[j].path[l->ants[j].pos++]].attr &= ~VTX_ANT;
					n++;
				}
				else if (!(l->vertices[l->ants[j].path[l->ants[j].pos + 1]].attr & VTX_ANT))
				{
					c = 1;
					l->ants[j].moved = 1;
					l->vertices[l->ants[j].path[l->ants[j].pos + 1]].attr |= VTX_ANT;
					l->vertices[l->ants[j].path[l->ants[j].pos++]].attr &= ~VTX_ANT;
					n++;
				}
			}
			j++;
		}
		j = 0;
		while (j < l->num_ants)
		{
			if (l->ants[j].moved)
			{
				l->ants[j].moved = 0;
				ft_printf("L%d-%s%c", l->ants[j].num, l->vertices[l->ants[j].path[l->ants[j].pos]].name, --n ? ' ' : '\n');
			}
			j++;
		}
	}
}

void	display_vertices(t_lemin *l)
{
	int		i;

	i = 0;
	while (i < l->num_rooms)
	{
		ft_printf("%d: %s\n", l->vertices[i].n, l->vertices[i].name);
		i++;
	}
}

void	fill_vertices(t_lemin *l)
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

int		scrub_path(t_lemin *l)
{
	t_graph	*graph;
	int		i;

	display_vertices(l);
	graph = create_graph(l->num_rooms);
	graph->matrix = l->adj_mtx;
	dfs(graph, l->start, l->end);
	//TODO free stuff
	if (!graph->shortest)
		return (1);
	i = 0;
	while (i < graph->size)
	{
		ft_printf(i < graph->size - 1 ? "%d -> " : "%d\n", graph->shortest[i]);
		i++;
	}
	set_ants(l, graph);
	fill_vertices(l);
	ft_printf("Moving ants\n");
	move_ants(l);
	return (0);
}
