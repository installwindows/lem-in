/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 21:05:14 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/03 19:59:59 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct		s_adj_node
{
	int					dest;
	struct s_adj_node	*next;
}					t_adj_node;

typedef struct		s_adj_list
{
	t_adj_node		*head;
}					t_adj_list;

typedef struct		s_graph
{
	int				v;
	t_adj_list		*array;
}					t_graph;

t_adj_node	*new_adj_node(int dest)
{
	t_adj_node *node;

	node = malloc(sizeof(t_adj_node));
	if (node == NULL)
		return (NULL);
	node->dest = dest;
	node->next = NULL;
	return (node);
}

t_graph		*create_graph(int v)
{
	int		i;
	t_graph	*graph;

	graph = malloc(sizeof(t_graph));
	graph->v = v;
	graph->array = malloc(sizeof(t_adj_list) * v);
	i = 0;
	while (i < v)
		graph->array[i++].head = NULL;
	return (graph);
}

void		add_edge(t_graph *graph, int src, int dest)
{
	t_adj_node	*node;

	node = new_adj_node(dest);
	node->next = graph->array[src].head;
	graph->array[src].head = node;
	node = new_adj_node(src);
	node->next = graph->array[dest].head;
	graph->array[dest].head = node;
}

void		print_graph(t_graph *graph)
{
	int			v;
	t_adj_node	*node;

	v = 0;
	while (v < graph->v)
	{
		node = graph->array[v].head;
		ft_printf("Adjacency list of vertex %d\n head ", v);
		while (node)
		{
			ft_printf("-> %d", node->dest);
			node = node->next;
		}
		ft_printf("\n");
		v++;
	}
}

int		main(void)
{
	int		v = 5;
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
}
