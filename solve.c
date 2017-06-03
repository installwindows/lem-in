/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 14:38:57 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/02 23:35:27 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	solve(t_lemin *l, int cur, int dest)
{
	l->visited[cur] = 1;
	path[l->path_index]
}

int			dfs(t_lemin *l)
{
	int		visited[l->num_rooms];
	int		path[l->num_rooms];
	int		i;

	ft_memset(visited, 0, sizeof(int) * l->num_rooms);
	i = 0;
	solve(l, visited, path, i);
}
