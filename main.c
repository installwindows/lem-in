/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 21:15:38 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/16 04:30:38 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	cleanup(char **file)
{
	int		i;

	i = 0;
	if (file)
		while (file[i])
			free(file[i++]);
	free(file);
}

static void	free_lemin(t_lemin *lemin)
{
	int		i;
	t_room	*c;

	delete_graph(lemin->graph);
	i = 0;
	if (lemin->adj_mtx)
		while (lemin->adj_mtx[i])
			free(lemin->adj_mtx[i++]);
	free(lemin->adj_mtx);
	i = 0;
	if (lemin->vertices)
		while (i < lemin->num_rooms)
			free(lemin->vertices[i++].name);
	free(lemin->vertices);
	free(lemin->ants);
	c = lemin->rooms;
	while (c)
	{
		lemin->rooms = c->next;
		free(c->name);
		free(c);
		c = lemin->rooms;
	}
	cleanup(lemin->file);
}

static void	display_file(char **file)
{
	int		i;

	i = 0;
	while (file[i])
	{
		if (file[i][0] == '#' && file[i][1] != '#')
		{
			i++;
			continue ;
		}
		ft_printf("%s\n", file[i++]);
	}
}

int			main(void)
{
	t_lemin	lemin;
	int		err;

	err = 0;
	ft_memset(&lemin, (err = 0), sizeof(t_lemin));
	if (!(lemin.file = validate_file()))
		ft_fprintf((err = 2), "File's not fine.\n");
	if (!err && parse(&lemin))
		ft_fprintf((err = 2), "Data's not right.\n");
	if (!err && scrub_path(&lemin))
		ft_fprintf((err = 2), "There is no path!\n");
	if (!err)
	{
		display_file(lemin.file);
		ft_printf("\n");
		move_ants(&lemin);
	}
	free_lemin(&lemin);
	return (err);
}
