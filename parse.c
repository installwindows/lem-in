/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 21:42:43 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/28 00:26:44 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lemin	*parse_input(void)
{
	t_lemin	*lemin;
	int		r;
	char	*line;

	lemin = malloc(sizeof(t_lemin));
	ft_memset(lemin, 0, sizeof(t_lemin));
	lemin->adj_mtx = parse_header(void);
	lemin->vertices = parse_rooms(void);
	parse_links(lemin);
	while ((r = gnl(0, &line)) && r != -1)
	{
		
	}
}
