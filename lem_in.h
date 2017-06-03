/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 21:17:35 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/02 23:35:27 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
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
	int				room;
	int				done;
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
}					t_lemin;


char				**validate_file(void);
void				*free_lemin(t_lemin *lemin);
int					parse(t_lemin *lemin);
t_room				*find_room(t_room *lst, char *name, int num);

#endif
