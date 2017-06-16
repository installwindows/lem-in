/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 21:05:14 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/16 03:44:49 by varnaud          ###   ########.fr       */
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
			cur = graph->array[i].head->next;
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
		j = -1;
		while (++j < graph->v)
			ft_printf(j < graph->v - 1 ? "%d " : "%d\n", graph->matrix[i][j]);
		i++;
	}
}
