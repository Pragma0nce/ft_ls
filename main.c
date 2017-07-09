/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 12:30:48 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/07/09 17:18:33 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_default(char *dir, t_format *format)
{
	struct dirent	*list;
	int				i;
	int				len;

	i = 0;
	list = load_list(dir, &len);
	if (format->has_r)
		sort_list_reverse(list, len);
	if (format->has_t)
	{
		if (format->has_r)
			sort_by_time_reversed(list, len, dir);
		else
			sort_by_time(list, len, dir);
	}
	if (format->has_l)
	{
		display_long_format(list, len, format, dir);
		return ;
	}
	while (i++ < len)
		if ((list[i].d_name[0] == '.' && format->has_a) ||
				(list[i].d_name[0] != '.'))
			ft_printf("%s\t", list[i].d_name);
	ft_printf("\n");
}

int		main(int argc, char **argv)
{
	parse_parameters(argc, argv);
	return (0);
}
