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


void	sort_list_reverse(struct dirent *list, int size)
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
			if (ft_strcmp(list[d].d_name, list[d + 1].d_name) < 0)
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


void	sort_by_time(struct dirent *list, int size)
{
	int n;
	int c;
	int d;
	struct dirent temp;
    struct stat sb;
    struct stat sb2;
    char *time1;
    char *time2;

	n = size;
	c = 0;
	d = 0;
	while (c < n - 1)
	{
		d = 0;
		while (d < n - c - 1)
		{
            stat(list[d].d_name, &sb);
			stat(list[d + 1].d_name, &sb2);
            if (difftime(sb.st_mtime, sb2.st_mtime) == 0)
            {
                if (ft_strcmp(list[d].d_name, list[d + 1].d_name) > 0)
                {
                    //printf("fek man\n");
                    temp = list[d];
                    list[d] = list[d + 1];
                    list[d + 1] = temp;
                }
            }
            else if (difftime(sb.st_mtime, sb2.st_mtime) < 1)
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


void	sort_by_time_reversed(struct dirent *list, int size)
{
	int n;
	int c;
	int d;
	struct dirent temp;
    struct stat sb;
    struct stat sb2;
    char *time1;
    char *time2;

	n = size;
	c = 0;
	d = 0;
	while (c < n - 1)
	{
		d = 0;
		while (d < n - c - 1)
		{
            stat(list[d].d_name, &sb);
			stat(list[d + 1].d_name, &sb2);
    
            if (difftime(sb.st_mtime, sb2.st_mtime) > 1)
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

    //printf("+++ load_list: Attempting to read from %s\n", directory_path);
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

void    display_default(char *dir, t_format *format)
{
    
    struct dirent *list;
    int i = 0;
    int len;
    // Loop going through

    list = load_list(dir, &len);
    
    if (format->has_r)
        sort_list_reverse(list, len);
    if (format->has_t)
    {   
        if (format->has_r)
            sort_by_time_reversed(list, len);
        else
            sort_by_time(list, len);
    }
    if (format->has_l)
    {
        display_long_format(list, len, format);
        return;    
    }
    while (i < len)
    {
        if ((list[i].d_name[0] == '.' && format->has_a) || (list[i].d_name[0] != '.'))
            printf("%s\t", list[i].d_name);
        i++;
    }	
    printf("\n");
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

    select_mode(option_list, path_list);
    //print_options(option_list);
    //print_paths(path_list);
}

t_format    *set_format(BOOL a, BOOL l, BOOL r, BOOL t)
{
    t_format *format;
    format = (t_format*)malloc(sizeof(t_format));

    format->has_a = a;
    format->has_l = l;
    format->has_r = r;
    format->has_t = t;
    return (format);
}

void    select_mode(t_option *option, t_path *path)
{
    t_format *format;
    t_option *option_head;
    BOOL    recursive;
    format = set_format(FALSE, FALSE, FALSE, FALSE);

    recursive = FALSE;
    option_head = option;
    while (option_head != NULL)
    {
        if (option_head->option == 'a')
            format->has_a = TRUE;
        else if (option_head->option == 'l')
            format->has_l = TRUE;
        else if (option_head->option == 'r')
            format->has_r = TRUE;
        else if (option_head->option == 't')
            format->has_t = TRUE;
        else if (option_head->option == 'R')
            recursive = TRUE;
        option_head = option_head->next;
    }
    if (recursive == TRUE)
        display_recursive(path->path_name, format);
    else
        display_default(path->path_name, format);
}

int	main(int argc, char **argv)
{
    char            dir_name;
    struct dirent   *list;
    int             len_list;
    int             i; 

    parse_parameters(argc, argv);
    //list = load_list("../", &len_list);
    // Display everything
    //display_default(list, len_list);
    //display_long_format(list, len_list);
	//display_all(list, len_list);
    //printf("Path list: %s\n", path_list->path_name);
    //recursive(path_list->path_name);
    return (0);
}
