#include "ft_ls.h"

void    set_path(t_directory *dir, char *str)
{
    if (ft_strlen(str) > dir->max_len)
    {
        free(dir->path);
        dir->path = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1));
        dir->max_len = ft_strlen(str);
    }

    ft_strcpy(dir->path, str);
    dir->path_len = ft_strlen(str);
}

void    push_path(t_directory *dir, char *str)
{
    char *temp;

    if (dir->path_len + ft_strlen(str) >= dir->max_len)
    {
        temp = (char*)malloc(sizeof(char) * dir->max_len);
        strcpy(temp, dir->path);
        free(dir->path);
        dir->path = (char*)malloc(sizeof(char) * (dir->max_len + ft_strlen(str) + 2));
        dir->max_len = (dir->max_len + ft_strlen(str) + 1);
        strcpy(dir->path, temp);
        dir->path = ft_strjoin(dir->path, str);
        dir->path_len = ft_strlen(dir->path);
        free(temp);
    }
    else
    {

        dir->path = ft_strjoin(dir->path, str);
        dir->path_len = ft_strlen(dir->path);
    }
}

void    pop_path(t_directory *dir)
{
    int i;

    i = dir->path_len;
    while (i > 0 && dir->path[i] != '/')
    {
        dir->path[i] = '\0';;
        i--;
    }
    dir->path[i] = '\0';
    dir->path_len = ft_strlen(dir->path);
}
