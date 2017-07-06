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
#include <sys/stat.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include <time.h>

void    test_stat(struct stat sb)
{
    char *time; 
    //printf("Mode: %lo (octal)\n", (unsigned long) sb.st_mode);
    // Size
    printf("%ld\t", sb.st_size); 
    // Last time modified
    time = ctime(&sb.st_mtime);
    time[ft_strlen(time) - 1] = '\0';
    printf("%s ", time);

}

void    print_permissions(mode_t mode)
{
    printf(S_ISDIR(mode) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}


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

void    display_default(struct dirent *list, int size)
{
    // Loop going through
	while (size--)
	{
		if (list[size].d_name[0] != '.')
		printf("%s\t", list[size].d_name);
	}	
}

void    display_long_format(struct dirent *list, int size)
{
    int i;
    struct stat sb;

    i = 0;
    while (i < size)
    {
        if (list[i].d_name[0] != '.')
        {
            stat(list[i].d_name, &sb);
	        print_permissions(sb.st_mode);
            printf("\t");
            test_stat(sb);
            printf("%s\t", list[i].d_name);
        }
        printf("\n");
        i++;
    }
    printf("\n");
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

    // Display everything
    //display_default(list, len_list);
    display_long_format(list, len_list);
	return (0);
}
