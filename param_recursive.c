#include "ft_ls.h"

void recursive(char *dir_name)
{
    struct dirent *list;
    int len;
    int i;
    //static char *path;
    static t_directory directories;

    if (directories.path == NULL)
    {
        directories.max_len = 100;
        directories.path = (char*)malloc(sizeof(char) * (directories.max_len + 1));
        set_path(&directories, dir_name);
    }

    /*if (path == NULL)
    {   
        path = (char*)malloc(sizeof(char) * 100);
        ft_strcpy(path, dir_name);
        printf("---------------- %s\n", path);
    }*/

    i = 2;
    list = load_list(dir_name, &len);
    printf("%s:\n", dir_name);
    while (i < len)
    {
        printf("%s  ", list[i].d_name);
        i++;
    }
    printf("\n\n");
    i = 2;
    while (i < len)
    {
        if (list[i].d_type == DT_DIR)
        {
            //path = ft_strjoin(path, "/");
            //path = ft_strjoin(path, list[i].d_name);
            //printf(" ------------------ Current path: %s\n", path);
            push_path(&directories, list[i].d_name);
            recursive(directories.path);
            pop_path(&directories);
            //free(list);
        }
        i++;
    }
}
