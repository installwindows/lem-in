/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 21:15:38 by varnaud           #+#    #+#             */
/*   Updated: 2017/05/27 23:31:56 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lemin	*lemin;

	lemin = parse_input();
	if (!lemin)
	{
		ft_fprintf(2, "File's not fine.\n");
		return (1);
	}
	display_lemin(lemin);
}
