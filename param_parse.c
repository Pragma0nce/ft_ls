/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 14:26:37 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/07/09 15:27:19 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_option	*add_option(char opt, t_option *list)
{
	t_option *temp;

	temp = (t_option*)malloc(sizeof(t_option));
	temp->option = opt;
	temp->next = list;
	return (temp);
}

void		print_options(t_option *list)
{
	while (list != NULL)
	{
		ft_printf("Option added: %c\n", list->option);
		list = list->next;
	}
}

t_path		*add_path(char *path_name, t_path *list)
{
	t_path *temp;

	temp = (t_path*)malloc(sizeof(t_path));
	temp->path_name = path_name;
	temp->next = list;
	return (temp);
}

void		print_paths(t_path *list)
{
	while (list != NULL)
	{
		ft_printf("Path added: %s\n", list->path_name);
		list = list->next;
	}
}
