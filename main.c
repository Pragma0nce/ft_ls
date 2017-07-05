/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 13:40:50 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/07/05 14:48:20 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include "libft.h"

void	sort_list(struct dirent *list, int size)
{
	int n;
	int c;
	int d;
	struct dirent temp;

	n = size;
	c = 0;
	d = 0;
	while (c < n - 1)
	{
		d = 0;
		while (d < n - c - 1)
		{
			if (ft_strcmp(list[d].d_name, list[d + 1].d_name) > 0)
			{
				temp = list[d];
				list[d] = list[d + 1];
				list[d + 1] = temp;
			}
			d++;
		}
		c++;
	}
}

int	main(int argc, char **argv)
{
	struct dirent *list;
	DIR *dir;
	int len_list;
	int i;

	i = 0;
	len_list = 0;
	dir = opendir(".");
	while ((list = readdir(dir)) != NULL)
		len_list++;
	closedir(dir);

	dir = opendir(".");
	i = 0;
	list = (struct dirent*)malloc(sizeof(struct dirent) * len_list);
	while (i < len_list)
	{
		list[i] = *(readdir(dir));
		i++;
	}
	sort_list(list, len_list);
	i = 0;
	while (i < len_list)
	{
		if (list[i].d_name[0] != '.')
		printf("%s\t", list[i].d_name);
		i++;
	}	
	return (0);
}
