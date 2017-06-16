/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 03:04:49 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/16 03:08:40 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			print_stack_elements(t_graph *graph, t_dfs *dfs)
{
	int		i;

	i = 0;
	if (dfs->index < graph->size)
	{
		graph->size = dfs->index;
		free(graph->shortest);
		graph->shortest = malloc(sizeof(int) * dfs->index);
		ft_memcpy(graph->shortest, dfs->path, sizeof(int) * dfs->index);
	}
}

static void			print_path(t_graph *graph, t_dfs *dfs, int src, int dest)
{
	int		i;

	dfs->visited[src] = 1;
	dfs->path[dfs->index] = src;
	dfs->index++;
	if (src == dest)
		print_stack_elements(graph, dfs);
	else
	{
		i = 0;
		while (i < graph->v)
		{
			if (dfs->visited[i] == 0 && graph->matrix[src][i])
				print_path(graph, dfs, i, dest);
			i++;
		}
	}
	dfs->visited[src] = 0;
	dfs->index--;
}

void				dfs(t_graph *graph, int src, int dest)
{
	int		visited[graph->v];
	int		path[graph->v];
	t_dfs	dfs;

	ft_memset(visited, 0, sizeof(int) * graph->v);
	ft_memset(path, 0, sizeof(int) * graph->v);
	dfs.visited = visited;
	dfs.path = path;
	dfs.v = graph->v;
	dfs.index = 0;
	graph->size = 2147483647;
	free(graph->shortest);
	graph->shortest = NULL;
	print_path(graph, &dfs, src, dest);
}
