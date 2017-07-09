/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 14:35:08 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/07/09 17:18:30 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	swap(struct dirent list[], int index)
{
	struct dirent temp;

	temp = list[index];
	list[index] = list[index + 1];
	list[index + 1] = temp;
}

void	sort_list(struct dirent *list, int n)
{
	int				c;
	int				d;
	int				off_1;
	int				off_2;

	c = 0;
	while (c < n - 1)
	{
		d = 0;
		while (d < n - c - 1)
		{
			off_1 = 0;
			off_2 = 0;
			if (list[d].d_name[0] == '.' || list[d].d_name[0] == '\\')
				off_1 = 1;
			if (list[d + 1].d_name[0] == '.' || list[d].d_name[0] == '\\')
				off_2 = 1;
			if (ft_strcmp(&(list[d].d_name[off_1]),
						&(list[d + 1].d_name[off_2])) > 0)
				swap(list, d);
			d++;
		}
		c++;
	}
}

void	sort_list_reverse(struct dirent *list, int n)
{
	int				c;
	int				d;
	int				off_1;
	int				off_2;

	c = 0;
	while (c < n - 1)
	{
		d = 0;
		while (d < n - c - 1)
		{
			off_1 = 0;
			off_2 = 0;
			if (list[d].d_name[0] == '.' || list[d].d_name[0] == '\\')
				off_1 = 1;
			if (list[d + 1].d_name[0] == '.' || list[d].d_name[0] == '\\')
				off_2 = 1;
			if (ft_strcmp(&(list[d].d_name[off_1]),
						&(list[d + 1].d_name[off_2])) < 0)
				swap(list, d);
			d++;
		}
		c++;
	}
}
