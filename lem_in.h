/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 21:17:35 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/01 19:17:58 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# define VTX_START 1
# define VTX_END 2
# define VTX_ANT 4

typedef struct	s_ant
{
	int			num;
	int			room;
	int			done;
}				t_ant;

typedef struct	s_vertex
{
	int			x;
	int			y;
	int			n;
	char		*name;
	int			weight;
	int			attr;
}				t_vertex;

typedef struct	s_lemin
{
	int			num_ants;
	t_ant		*ants;
	int			**adj_mtx;
	t_vertex	*vertices;
	int			num_rooms;
}				t_lemin;


char			**validate_file(void);
void			*free_lemin(t_lemin *lemin);

#endif
