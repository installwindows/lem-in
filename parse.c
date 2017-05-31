/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 21:42:43 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/31 00:37:52 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		*free_lemin(t_lemin *lemin)
{
	int		i;

	if (lemin == NULL)
		return (NULL);
	i = 0;
	if (lemin->adj_mtx)
		while (lemin->adj_mtx[i])
			free(lemin->adj_mtx[i++]);
	free(lemin->adj_mtx);
	free(lemin->vertices);
	free(lemin->ants);
	free(lemin);
	return (NULL);
}

static int	num_of_rooms(t_lemin *lemin, int *i, char **file)
{
	int		n;
	int		i;

	n = 0;
	while (file[*i])
	{
		if (file[*i][0] != '#')
			n++;
		++(*i);
	}
	lemin->num_rooms = n;
	lemin->adj_mtx = malloc(sizeof(int*) * (n + 1));
	i = 0;
	while (i < n)
	{
		lemin->adj_mtx[i] = malloc(sizeof(int) * n);
		ft_memset(lemin->adj_mtx[i], 0, sizeof(int) * n);
		i++;
	}
	lemin->adj_mtx[i] = NULL;
	lemin->vertices = malloc(sizeof(t_vertex) * n);
	ft_memset(lemin->vertices, 0, sizeof(t_vertex) * n);
	return (n);
}

static int	parse_header(t_lemin *lemin, int *i, char **file)
{
	while (file[*i])
		if (file[*i][0] == '#' && file[*i][1] == '#')
			(*i)++;
		else if (ft_natoi(file[*i], &lemin->num_ants))
			break ;
		else
			return (++(*i) && 0);
	return (1);
}

static int	parse_rooms(t_lemin *lemin, int *i, char **file)
{
	char	**split;

	if (!num_of_rooms(lemin, i, file))
		return (1);
	while (file[*i])
	{
		
	}
	return (0);
}

static int	parse_links(t_lemin *lemin, int *i, char **file)
{
	return (0);
}

t_lemin		*parse_input(char **file)
{
	t_lemin	*lemin;
	int		i;

	lemin = malloc(sizeof(t_lemin));
	ft_memset(lemin, 0, sizeof(t_lemin));
	i = 0;
	if (parse_header(lemin, &i, file) || parse_rooms(lemin, &i, file) ||
		parse_links(lemin, &i, file))
		return (free_lemin(lemin));
	return (lemin);
}
