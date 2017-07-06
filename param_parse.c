#include "ft_ls.h"

t_option    *add_option(char opt, t_option *list)
{
    t_option *temp;
    temp = (t_option*)malloc(sizeof(t_option));

    temp->option = opt;
    temp->next = list;

    return (temp);
}

void        print_options(t_option *list)
{
    while (list != NULL)
    {
        printf("Option added: %c\n", list->option);
        list = list->next;
    }
}

t_path      *add_path(char *path_name, t_path *list)
{
    t_path *temp;
    temp = (t_path*)malloc(sizeof(t_option));

    temp->path_name = path_name;
    temp->next = list;

    return (temp);
}


void        print_paths(t_path *list)
{
    while (list != NULL)
    {
        printf("Path added: %s\n", list->path_name);
        list = list->next;
    }
}
