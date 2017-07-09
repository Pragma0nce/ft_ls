#include "ft_ls.h"


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
                else
                {
                    printf("invalid option -- %s\n", &(argv[i][j]));
                    exit(0);
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
    int len;

    recursive = FALSE;
    option_head = option;
    if (path == NULL)
        path = add_path(".", path);
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
    {  
        len = get_path_length(path);
        while (path != NULL)
        {
            if (len >= 2)
                printf("%s:\n", path->path_name);
            display_default(path->path_name, format);
            path = path->next;
            printf("\n");
        }
    }
}
