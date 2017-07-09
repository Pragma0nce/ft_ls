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

void    display_default(char *dir, t_format *format)
{
    
    struct dirent *list;
    int i;
    int len;
    // Loop going through
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
