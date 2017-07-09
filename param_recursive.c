#include "ft_ls.h"

void display_recursive(char *dir, t_format *format)
{
    struct dirent *list;
    int len;
    int i;
    //static char *path;
    static t_directory directories;

    //printf("dir to search: %s \n", dir);
    //getchar();
    if (directories.path == NULL)
    {
        directories.max_len = 100;
        directories.path = (char*)malloc(sizeof(char) * (directories.max_len + 1));
        set_path(&directories, dir);
    }
   
    i = 0;
    list = load_list(dir, &len);
    
    if (format->has_l)
    {
        printf("%s: \n", dir);
        //getchar();
        display_long_format(list, len, format, dir);
    }
    else 
    {
        printf("%s:\n", dir);
        while (i < len)
        {
            if ((list[i].d_name[0] == '.' && format->has_a) || (list[i].d_name[0] != '.'))
                printf("%s  ", list[i].d_name);
            i++;
        }
    }
    
    i = 0;
    //printf("\n");
    while (i < len)
    {
        /*if (list[i].d_type == DT_DIR)
        {
            printf("%s is a directory\n", list[i].d_name);
            getchar();
        }*/
        if (list[i].d_type == DT_DIR && ((list[i].d_name[0] == '.' && format->has_a) || (list[i].d_name[0] != '.')))
        {
            if ((list[i].d_name[0] == '.' && list[i].d_name[1] == 0) || (list[i].d_name[0] == '.' && list[i].d_name[1] == '.'))
                i++;
            else
            {
                push_path(&directories, list[i].d_name);
                display_recursive(directories.path, format);
                pop_path(&directories);                
            }
            //free(list);
        }
        i++;
    }
}
