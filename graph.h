/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 21:32:36 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/05 04:10:13 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_H
# define GRAPH_H
# include "libft.h"

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
	int				index;
	t_adj_list		*array;
	int				**matrix;
}					t_graph;

typedef struct		s_dfs
{
	int				*visited;
	int				*path;
	int				index;
	int				v;
}					t_dfs;

void				print_graph(t_graph *graph);
void				add_edge(t_graph *graph, int src, int dest);
t_graph				*create_graph(int v);

#endif
