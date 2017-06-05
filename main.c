/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 21:15:38 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/05 05:27:58 by varnaud          ###   ########.fr       */
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

void		*free_lemin(t_lemin *lemin)
{
	int		i;
	t_room	*c;

	if (lemin == NULL)
		return (NULL);
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
	return (NULL);
}

static void	display_file(char **file)
{
	int		i;

	i = 0;
	while (file[i])
		ft_printf("%s\n", file[i++]);
	ft_printf("\n");
}

void	display_lemin(t_lemin *l)
{
	int		i;
	int		j;
	t_room	*c;
	t_room	*a;
	t_room	*b;

	ft_printf("%d\n", l->num_ants);
	c = l->rooms;
	while (c)
	{
		if (c->f & VTX_START)
			ft_printf("##start\n");
		if (c->f & VTX_END)
			ft_printf("##end\n");
		ft_printf("%s(%d) %d %d\n", c->name, c->num, c->x, c->y);
		c = c->next;
	}
	i = 0;
	j = 0;
	while (l->adj_mtx[i])
	{
		j = i + 1;
		while (j < l->num_rooms)
		{
			if (l->adj_mtx[i][j])
			{
				a = find_room(l->rooms, NULL, i);
				b = find_room(l->rooms, NULL, j);
				ft_printf("%s-%s\n", a->name, b->name);
			}
			j++;
		}
		i++;
	}
}

int		main(void)
{
	t_lemin	lemin;
	int		err;

	err = 0;
	ft_memset(&lemin, 0, sizeof(t_lemin));
	if (!(lemin.file = validate_file()))
	{
		ft_fprintf(2, "File's not fine.\n");
		err = 1;
	}
	if (!err && parse(&lemin))
	{
		ft_fprintf(2, "Data's not right.\n");
		err = 1;
	}
	if (!err)
		display_lemin(&lemin);
	scrub_path(&lemin);
	free_lemin(&lemin);
	return (err);
}
