#include "ft_ls.h"

void display_recursive(char *dir, t_format *format)
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
        set_path(&directories, dir);
    }

        i = 2;
        list = load_list(dir, &len);
        printf("%s:\n", dir);
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
                push_path(&directories, list[i].d_name);
                display_recursive(directories.path, format);
                pop_path(&directories);
                //free(list);
            }
            i++;
        }
}
