/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 21:42:43 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/01 23:27:10 by varnaud          ###   ########.fr       */
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
	i = 0;
	while (i < lemin->num_rooms)
		free(lemin->vertices[i].name);
	free(lemin->vertices);
	free(lemin->ants);
	free(lemin);
	return (NULL);
}

static int	num_of_rooms(t_lemin *lemin, int i, char **file)
{
	int		n;
	int		i;

	n = 0;
	while (file[i] && ft_strchr(file[i], '-'))
	{
		if (file[i][0] != '#')
			n++;
		++(i);
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
		if (file[*i][0] == '#')
			(*i)++;
		else if (ft_natoi(file[*i], &lemin->num_ants))
			break ;
		else
			return (++(*i) && 0);
	return (1);
}

static int	parse_command(char *command)
{
	if (!ft_strcmp(command, "##start"))
		return (VTX_START);
	else if (!ft_strcmp(command, "##end"))
		return (VTX_END);
	return (0);
}

static int	add_room(t_lemin, int f, int n, char *s)
{
	char	**split;
	int		i;
	int		err;

	if (!(split = ft_strsplit(s, ' ')))
		return (1);
	i = 0;
	err = 0;
	lemin->vertices[lemin->num_rooms - n - 1].attr = f;
	while (split[i])
	{
		if (i == 0)
		{
			if (split[i][0] == 'L' || split[i][0] == '#')
				err = 1;
			lemin->vertices[lemin->num_rooms - n - 1].n = lemin->num_rooms - n - 1;
			lemin->vertices[lemin->num_rooms - n - 1].name = ft_strdup(split[i]);
		}
		else if (i == 1 && !err)
			err = ft_natoi(split[i], &lemin->vertices[lemin->num_rooms - n - 1].x);
		else if (i == 2 && !err)
			err = ft_natoi(split[i], &lemin->vertices[lemin->num_rooms - n - 1].y);
		i++;
	}
	if (i != 3)
		err = 1;
	i = 0;
	while (split[i])
		free(split[i]);
	free(split);
	return (err);
}

static int	parse_rooms(t_lemin *lemin, int *i, char **file)
{
	int		f;
	int		n;

	if (!(n = num_of_rooms(lemin, *i, file)))
		return (1);
	while (file[*i] && n--)
	{
		f = 0;
		while (file[*i][0] == '#')
			f |= parse_command(file[(*i)++]);
		if (file[*i][0] == 'L')
			return (1);
		if (add_room(lemin, f, n, file[*i]))
			return (1);
		(*i)++;
	}
	return (0);
}

static int	parse_links(t_lemin *lemin, int *i, char **file)
{
	char	**split;
	int		i;
	int		n;

	while (file[*i])
	{
		if (!(split = ft_split(file[*i], ft_strlen(file[*i]), &n)))
			return (1);
		
		++*i;
	}
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
