/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 12:09:03 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/07/09 15:27:16 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parse_options(char **argv, int i, int j, t_option **option_list)
{
	while (argv[i][j])
	{
		if (argv[i][j] == 'l' || argv[i][j] == 'R' || argv[i][j] == 'a'
				|| argv[i][j] == 'r' || argv[i][j] == 't')
		{
			*option_list = add_option(argv[i][j], *option_list);
		}
		else
		{
			printf("invalid option -- %s\n", &(argv[i][j]));
			exit(0);
		}
		j++;
	}
}

void	parse_path(char **argv, int i, int j, t_path **path_list)
{
	int		len;
	char	*temp_path;

	len = ft_strlen(&(argv[i][j]));
	temp_path = (char*)malloc(sizeof(char) * (len + 1));
	while (argv[i][j])
	{
		temp_path[j] = argv[i][j];
		j++;
	}
	*path_list = add_path(temp_path, *path_list);
}

void	parse_parameters(int argc, char **argv)
{
	int			i;
	int			j;
	t_option	*option_list;
	t_path		*path_list;

	path_list = NULL;
	option_list = NULL;
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			j = 1;
			parse_options(argv, i, j, &option_list);
		}
		else
		{
			j = 0;
			parse_path(argv, i, j, &path_list);
		}
		i++;
	}
	select_mode(option_list, path_list);
}
