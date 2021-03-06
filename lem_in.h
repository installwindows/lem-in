/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 21:17:35 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/16 04:09:39 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include "graph.h"
# define VTX_START 1
# define VTX_END 2
# define VTX_ANT 4
# define VTX_VISITED 8

typedef struct		s_room
{
	int				num;
	int				x;
	int				y;
	int				f;
	char			*name;
	struct s_room	*next;
}					t_room;

typedef struct		s_ant
{
	int				num;
	int				pos;
	int				done;
	int				*path;
	int				size;
	int				moved;
}					t_ant;

typedef struct		s_vertex
{
	int				x;
	int				y;
	int				n;
	char			*name;
	int				weight;
	int				attr;
}					t_vertex;

typedef struct		s_lemin
{
	int				num_ants;
	int				num_rooms;
	int				**adj_mtx;
	char			**file;
	int				p;
	t_room			*rooms;
	t_room			**pr;
	t_ant			*ants;
	t_vertex		*vertices;
	int				has_start;
	int				has_end;
	int				*visited;
	int				*path;
	int				start;
	int				end;
	t_graph			*graph;
}					t_lemin;

char				**validate_file(void);
int					parse(t_lemin *lemin);
int					parse_hash(t_lemin *l);
int					parse_ants(t_lemin *l);
int					parse_links(t_lemin *l);
int					scrub_path(t_lemin *l);
void				set_ants(t_lemin *l, t_graph *g);
void				delete_graph(t_graph *graph);
int					pcleanup(char **s);
void				move_ants(t_lemin *l);

#endif
