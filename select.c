/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 12:24:19 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/07/09 12:28:34 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_format	*set_format(BOOL a, BOOL l, BOOL r, BOOL t)
{
	t_format *format;

	format = (t_format*)malloc(sizeof(t_format));
	format->has_a = a;
	format->has_l = l;
	format->has_r = r;
	format->has_t = t;
	return (format);
}

void		select_option(t_option **option_head, t_format *format,
													BOOL *recursive)
{
	while (*option_head != NULL)
	{
		if ((*option_head)->option == 'a')
			format->has_a = TRUE;
		else if ((*option_head)->option == 'l')
			format->has_l = TRUE;
		else if ((*option_head)->option == 'r')
			format->has_r = TRUE;
		else if ((*option_head)->option == 't')
			format->has_t = TRUE;
		else if ((*option_head)->option == 'R')
			*recursive = TRUE;
		*option_head = (*option_head)->next;
	}
}

void		select_mode(t_option *option, t_path *path)
{
	t_format	*format;
	t_option	*option_head;
	BOOL		recursive;
	int			len;

	format = set_format(FALSE, FALSE, FALSE, FALSE);
	recursive = FALSE;
	option_head = option;
	if (path == NULL)
		path = add_path(".", path);
	select_option(&option_head, format, &recursive);
	if (recursive == TRUE)
		display_recursive(path->path_name, format);
	else
	{
		len = get_path_length(path);
		while (path != NULL)
		{
			if (len >= 2)
				printf("%s:\n", path->path_name);
			display_default(path->path_name, format);
			path = path->next;
			printf("\n");
		}
	}
}
