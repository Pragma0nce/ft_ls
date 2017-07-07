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

#include "ft_ls.h"

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

int     count_num_files(char *directory_path)
{
    struct dirent *list;
    DIR *dir;
    int i;

    i = 0;
    dir = opendir(directory_path);
    while ((list = readdir(dir)) != NULL)
        i++;
    closedir(dir);
    return (i);
}


struct dirent   *load_list(char *directory_path, int *files_loaded)
{
    struct dirent *list;
    DIR *dir;
    int len_list;
    int i;

    i = 0;
    len_list = count_num_files(directory_path);
    dir = opendir(directory_path);
	list = (struct dirent*)malloc(sizeof(struct dirent) * len_list);
	while (i < len_list)
	{
		list[i] = *(readdir(dir));
		i++;
	}
	sort_list(list, len_list);
    *files_loaded = len_list;
    return(list);
}

void    display_default(struct dirent *list, int size)
{
    // Loop going through
	while (size--)
	{
		if (list[size].d_name[0] != '.')
		printf("%s\t", list[size].d_name);
	}	
}

void    parse_parameters(int argc, char **argv)
{
    int i;
    int j;
    int len;
    char *temp_path;
    
    t_option *option_list;
    t_path *path_list;

    path_list = NULL;
    option_list = NULL;
    i = 1;
    len = 0;
    while (i < argc)
    {
        if (argv[i][0] == '-') // If the first char of parameter is a - option
        {
            j = 1;
            while (argv[i][j])
            {
                if (argv[i][j] == 'l' || argv[i][j] == 'R' || argv[i][j] == 'a' || argv[i][j] == 'r' || argv[i][j] == 't')
                {
                    option_list = add_option(argv[i][j], option_list);
                }
                j++;
            }
        }
        else
        {
            j = 0;
            len = ft_strlen(&(argv[i][j]));
            temp_path = (char*)malloc(sizeof(char) * (len + 1));
            while (argv[i][j])
            {
                temp_path[j] = argv[i][j];
                j++;
            }
            path_list = add_path(temp_path, path_list);
                
        }
        i++;
    }

    print_options(option_list);
    print_paths(path_list);
}

void    recursive();
int	main(int argc, char **argv)
{
    char    dir_name;
    struct dirent   *list;
    int             len_list;
    int             i; 
    //parse_parameters(argc, argv);
    list = load_list("../recursion_test", &len_list);
    // Display everything
    display_default(list, len_list);
    //display_long_format(list, len_list);
	//display_all(list, len_list);
    recursive("../recursion_test");
    return (0);
}
