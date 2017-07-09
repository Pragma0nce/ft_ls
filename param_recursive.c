/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_recursive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 15:28:05 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/07/09 16:26:39 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void display_recursive(char *dir, t_format *format)
{
	struct dirent *list;
	struct stat sb;
	int len;
	int i;
	static t_directory directories;

	if (directories.path == NULL)
	{
		directories.max_len = 100;
		directories.path = (char*)malloc(sizeof(char) * (directories.max_len + 1));
		set_path(&directories, dir);
	}
   
	i = 0;
	list = load_list(dir, &len);
	
	if (format->has_l)
	{
		printf("%s: \n", dir);
		display_long_format(list, len, format, dir);
	}
	else 
	{
		printf("%s:\n", dir);
		while (i < len)
		{
			if ((list[i].d_name[0] == '.' && format->has_a) || (list[i].d_name[0] != '.'))
				printf("%s	", list[i].d_name);
			i++;
		}
	}
	
	i = 0;
	while (i < len)
	{
		if ((list[i].d_name[0] == '.' && list[i].d_name[1] == 0) || (list[i].d_name[0] == '.' && list[i].d_name[1] == '.'))
			;
		else
		{
			char *full = (char*)malloc(sizeof(char) * 100);
			full = ft_strcpy(full, directories.path);
			full = ft_strjoin(full, "/");
			full = ft_strjoin(full, list[i].d_name);
			int test = stat(full, &sb);

			//printf("%s <---- checking if this is a directory: stat result --- > %d \n", list[i].d_name, test);
			if (S_ISDIR(sb.st_mode))
				//printf(" +++ it is! \n");
			if (S_ISDIR(sb.st_mode) && ((list[i].d_name[0] == '.' && format->has_a) || (list[i].d_name[0] != '.')))
			{	
				push_path(&directories, list[i].d_name);
				//printf("%s <------ directories.path [%ld] \n", directories.path, sb.st_size);
				display_recursive(directories.path, format);
				pop_path(&directories);				   
			
				//free(list);
			}
		}
		i++;
	}
}
