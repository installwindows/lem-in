/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 21:05:14 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/05 05:24:12 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

static t_adj_node	*new_adj_node(int dest)
{
	t_adj_node *node;

	node = malloc(sizeof(t_adj_node));
	if (node == NULL)
		return (NULL);
	node->dest = dest;
	node->next = NULL;
	return (node);
}

t_graph				*create_graph(int v)
{
	int		i;
	t_graph	*graph;

	graph = malloc(sizeof(t_graph));
	graph->v = v;
	graph->array = malloc(sizeof(t_adj_list) * v);
	graph->matrix = malloc(sizeof(int*) * v);
	graph->shortest = NULL;
	graph->size = 2147483647;
	i = 0;
	while (i < v)
	{
		graph->array[i].head = NULL;
		graph->matrix[i] = malloc(sizeof(int) * v);
		ft_memset(graph->matrix[i], 0, sizeof(int) * v);
		i++;
	}
	return (graph);
}

void				delete_graph(t_graph *graph)
{
	int			i;
	t_adj_node	*cur;

	if (!graph)
		return ;
	i = 0;
	while (i < graph->v)
	{
		while (graph->array[i].head)
		{
			cur = graph->array[i].head->next;;
			free(graph->array[i].head);
			graph->array[i].head = cur;
		}
		free(graph->matrix[i]);
		i++;
	}
	free(graph->shortest);
	free(graph->matrix);
	free(graph->array);
	free(graph);
}

void				add_edge(t_graph *graph, int src, int dest)
{
	t_adj_node	*node;

	graph->matrix[src][dest] = 1;
	graph->matrix[dest][src] = 1;
	node = new_adj_node(dest);
	node->next = graph->array[src].head;
	graph->array[src].head = node;
	node = new_adj_node(src);
	node->next = graph->array[dest].head;
	graph->array[dest].head = node;
}

void				print_graph(t_graph *graph)
{
	int			i;
	int			j;
	t_adj_node	*node;

	i = 0;
	while (i < graph->v)
	{
		node = graph->array[i].head;
		ft_printf("Adjacency list of vertex %d\n head ", i);
		while (node)
		{
			ft_printf(node->next ? "-> %d " : "-> %d\n", node->dest);
			node = node->next;
		}
		i++;
	}
	i = 0;
	while (i < graph->v)
	{
		j = 0;
		while (j < graph->v)
		{
			ft_printf(j < graph->v - 1 ? "%d " : "%d\n", graph->matrix[i][j]);
			j++;
		}
		i++;
	}
}

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
	//while (i < dfs->index)
	//	ft_printf ("%d ", dfs->path[i++]);
	//ft_printf("\n");
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
	int		i;
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
	i = 0;
	ft_printf("Shortest path: ");
	if (graph->shortest)
		while (i < graph->size)
		{
			ft_printf(i < graph->size - 1 ? "%d -> " : "%d\n", graph->shortest[i]);
			i++;
		}
}

/*
int					main(void)
{
	int		v = 6;
	t_graph	*graph;

	graph = create_graph(v);
	add_edge(graph, 0, 1);
	add_edge(graph, 0, 4);
	add_edge(graph, 1, 2);
	add_edge(graph, 1, 3);
	add_edge(graph, 1, 4);
	add_edge(graph, 2, 3);
	add_edge(graph, 3, 4);
	print_graph(graph);
	ft_printf("Path from src to dest.\n");
	dfs(graph, 0, 5);
	delete_graph(graph);
}
*/
