/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 19:18:21 by varnaud           #+#    #+#             */
/*   Updated: 2017/06/02 04:54:45 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	cleanup(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
	gnl(-42, NULL);
}

static char	**list_to_array(t_list *lst, int size)
{
	char	**file;
	int		i;
	t_list	*cur;

	cur = lst;
	if (size <= 0 || lst == NULL)
		return (NULL);
	file = malloc(sizeof(char*) * (size + 1));
	i = 0;
	while (i < size)
	{
		file[i] = ft_strtrim(cur->content);
		cur = cur->next;
		i++;
	}
	file[i] = NULL;
	cleanup(lst);
	return (file);
}

char		**validate_file(void)
{
	t_list	*lst;
	t_list	**cur;
	char	*line;
	int		i;
	int		r;

	lst = NULL;
	cur = &lst;
	i = 0;
	while ((r = gnl(0, &line)) && r != -1)
	{
		(*cur) = malloc(sizeof(t_list));
		(*cur)->content = ft_strdup(line);
		(*cur)->next = NULL;
		cur = &(*cur)->next;
		i++;
		free(line);
	}
	return (list_to_array(lst, i));
}
