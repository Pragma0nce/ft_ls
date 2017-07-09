/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_recursive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 15:28:05 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/07/09 17:04:25 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_recursive(char *dir, t_format *format)
{
	struct dirent		*list;
	int					len;
	int					i;
	static t_directory	directories;

	if (directories.path == NULL)
		set_path(&directories, dir);
	i = 0;
	list = load_list(dir, &len);
	if (format->has_l)
	{
		ft_printf("%s: \n", dir);
		display_long_format(list, len, format, dir);
	}
	else
	{
		ft_printf("%s:\n", dir);
		while (i++ < len)
			if ((list[i].d_name[0] == '.' && format->has_a) ||
					(list[i].d_name[0] != '.'))
				ft_printf("%s	", list[i].d_name);
	}
	recursive_loop(list, &directories, len, format);
}

void	recursive_loop(struct dirent *list, t_directory *directories,
		int len, t_format *format)
{
	int			i;
	char		*full;
	struct stat	sb;

	i = -1;
	while (++i < len)
	{
		if (!((list[i].d_name[0] == '.' && list[i].d_name[1] == 0) ||
				(list[i].d_name[0] == '.' && list[i].d_name[1] == '.')))
		{
			full = (char*)malloc(sizeof(char) * 100);
			full = ft_strcpy(full, directories->path);
			full = ft_strjoin(full, "/");
			full = ft_strjoin(full, list[i].d_name);
			stat(full, &sb);
			if (S_ISDIR(sb.st_mode) && ((list[i].d_name[0] == '.'
							&& format->has_a) || (list[i].d_name[0] != '.')))
			{
				push_path(directories, list[i].d_name);
				display_recursive(directories->path, format);
				pop_path(directories);
			}
		}
	}
}
