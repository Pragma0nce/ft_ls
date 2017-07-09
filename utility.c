#include "ft_ls.h"


int     count_num_files(char *directory_path)
{
    struct dirent *list;
    DIR *dir;
    int i;

    i = 0;
    dir = opendir(directory_path);
    if (dir == NULL)
    {
        
        printf("cannot access '%s': No such file or directory\n", directory_path);
        exit(0);
    }
    while ((list = readdir(dir)) != NULL)
        i++;
    closedir(dir);
    return (i);
}


int     get_path_length(t_path *path)
{
    int len;

    len = 0;
    t_path *itr;
    itr = path;
    while (itr != NULL)
    {
        itr = itr->next;
        len++;
    }
    return (len);
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
