/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 21:05:14 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/02 23:35:27 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct		s_adj_node
{
	int					dest;
	void				*data;
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

t_adj_node	*new_adj_node(int dest, void *data, int size)
{
	t_adj_node *node;

	node = malloc(sizeof(t_adj_node));
	if (node == NULL)
		return (NULL);
	node->dest = dest;
	node->data = data;
	node->size = size;
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
	
}
