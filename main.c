/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 21:15:38 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/01 23:27:12 by varnaud          ###   ########.fr       */
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

static void	display_file(char **file)
{
	int		i;

	i = 0;
	while (file[i])
		ft_printf("%s\n", file[i++]);
	ft_printf("\n");
}

int		main(void)
{
	char	**file;
	//t_lemin	*lemin;

	file = validate_file();
	if (!file)
	{
		ft_fprintf(2, "File's not fine.\n");
		return (1);
	}
	display_file(file);
	cleanup(file);
	/*
	lemin = parse_input(file);
	if (!lemin)
	{
		ft_fprintf(2, "Data's not right.\n");
		return (1);
	}
	display_lemin(lemin);
	//cleanup;
	*/
}
