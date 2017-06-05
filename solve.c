/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 14:38:57 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/05 08:28:41 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	set_ants(t_lemin *l)
{
	int		i;

	l->ants = malloc(sizeof(t_ants) * l->num_ants);
	i = 0;
	while (i < l->num_ants)
	{

	}
}

int		scrub_path(t_lemin *l)
{
	t_graph	*graph;
	int		i;

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
	return (0);
}
