/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 21:17:35 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/27 22:19:11 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# define VTX_START 1
# define VTX_END 2

typedef struct	s_vertex
{
	int			x;
	int			y;
	int			n;
	int			weight;
	int			attr;
}				t_vertex;

typedef struct	s_lemin
{
	int			**adj_mtx;
	t_vertex	*vertices;
}				t_lemin;

#endif
