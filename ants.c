/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 03:10:24 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/16 03:18:00 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		set_ants(t_lemin *l, t_graph *g)
{
	int		i;

	l->ants = malloc(sizeof(t_ant) * l->num_ants);
	i = 0;
	while (i < l->num_ants)
	{
		l->ants[i].num = i + 1;
		l->ants[i].pos = 0;
		l->ants[i].done = 0;
		l->ants[i].path = g->shortest;
		l->ants[i].size = g->size;
		l->ants[i].moved = 0;
		i++;
	}
}

static void	loop_ants(t_lemin *l, int *c, int *n)
{
	int		j;

	j = -1;
	while (++j < l->num_ants)
		if (!l->ants[j].done)
		{
			if (l->vertices[l->ants[j].path[l->ants[j].pos + 1]].attr & VTX_END)
			{
				*c = 1;
				l->ants[j].done = 1;
				l->ants[j].moved = 1;
				l->vertices[l->ants[j].path[l->ants[j].pos++]].attr &= ~VTX_ANT;
				(*n)++;
			}
			else if (!(l->vertices[l->ants[j].path[l->ants[j].pos + 1]].attr &
																	VTX_ANT))
			{
				*c = 1;
				l->ants[j].moved = 1;
				l->vertices[l->ants[j].path[l->ants[j].pos + 1]].attr |=
																		VTX_ANT;
				l->vertices[l->ants[j].path[l->ants[j].pos++]].attr &= ~VTX_ANT;
				(*n)++;
			}
		}
}

void		move_ants(t_lemin *l)
{
	int		n;
	int		c;
	int		j;

	c = 1;
	while (c)
	{
		c = 0;
		n = 0;
		loop_ants(l, &c, &n);
		j = 0;
		while (j < l->num_ants)
		{
			if (l->ants[j].moved)
			{
				l->ants[j].moved = 0;
				ft_printf("L%d-%s%c", l->ants[j].num,
					l->vertices[l->ants[j].path[l->ants[j].pos]].name,
					--n ? ' ' : '\n');
			}
			j++;
		}
	}
}
