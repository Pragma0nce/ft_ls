/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 15:12:05 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/07/09 17:18:29 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	path_cpy(struct stat *sb, char *dir, struct dirent *list, int d)
{
	char *path_string;

	path_string = (char*)malloc(sizeof(char) *
			(ft_strlen(dir) + ft_strlen(list[d].d_name) + 1));
	ft_strcpy(path_string, dir);
	path_string = ft_strjoin(path_string, "/");
	path_string = ft_strjoin(path_string, list[d].d_name);
	lstat(path_string, sb);
	free(path_string);
}

void	sort_by_time(struct dirent *list, int n, char *dir)
{
	int				c;
	int				d;
	struct stat		sb;
	struct stat		sb2;

	c = 0;
	while (c < n - 1)
	{
		d = 0;
		while (d < n - c - 1)
		{
			path_cpy(&sb, dir, list, d);
			path_cpy(&sb2, dir, list, d + 1);
			if (difftime(sb.st_mtime, sb2.st_mtime) == 0)
			{
				if (ft_strcmp(list[d].d_name, list[d + 1].d_name) > 0)
					swap(list, d);
			}
			else if (difftime(sb.st_mtime, sb2.st_mtime) < 1)
				swap(list, d);
			d++;
		}
		c++;
	}
}

void	sort_by_time_reversed(struct dirent *list, int n, char *dir)
{
	int				c;
	int				d;
	struct stat		sb;
	struct stat		sb2;

	c = 0;
	while (c < n - 1)
	{
		d = 0;
		while (d < n - c - 1)
		{
			path_cpy(&sb, dir, list, d);
			path_cpy(&sb2, dir, list, d + 1);
			if (difftime(sb.st_mtime, sb2.st_mtime) == 0)
			{
				if (ft_strcmp(list[d].d_name, list[d + 1].d_name) > 0)
					swap(list, d);
			}
			else if (difftime(sb.st_mtime, sb2.st_mtime) > 1)
				swap(list, d);
			d++;
		}
		c++;
	}
}
