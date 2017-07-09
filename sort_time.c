#include "ft_ls.h"

void	sort_by_time(struct dirent *list, int size, char *dir)
{
	int n;
	int c;
	int d;
	struct dirent temp;
    struct stat sb;
    struct stat sb2;
    char *time1;
    char *time2;
    char *path_string;

	n = size;
	c = 0;
	d = 0;
	while (c < n - 1)
	{
		d = 0;
		while (d < n - c - 1)
		{

            path_string = (char*)malloc(sizeof(char) * (ft_strlen(dir) + ft_strlen(list[d].d_name) + 1));
            ft_strcpy(path_string, dir);
            path_string = ft_strjoin(path_string, "/");
            path_string = ft_strjoin(path_string, list[d].d_name);
            lstat(path_string, &sb);
            free(path_string);
            //lstat(list[d].d_name, &sb);
			
            
            path_string = (char*)malloc(sizeof(char) * (ft_strlen(dir) + ft_strlen(list[d + 1].d_name) + 1));
            ft_strcpy(path_string, dir);
            path_string = ft_strjoin(path_string, "/");
            path_string = ft_strjoin(path_string, list[d + 1].d_name);
            lstat(path_string, &sb2);
            free(path_string);
            //lstat(list[d + 1].d_name, &sb2);
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


void	sort_by_time_reversed(struct dirent *list, int size, char *dir)
{
	int n;
	int c;
	int d;
	struct dirent temp;
    struct stat sb;
    struct stat sb2;
    char *time1;
    char *time2;
    char *path_string;
    //printf("sort_by_time_reversed called.\n");
	n = size;
	c = 0;
	d = 0;
	while (c < n - 1)
	{
		d = 0;
		while (d < n - c - 1)
		{

            path_string = (char*)malloc(sizeof(char) * (ft_strlen(dir) + ft_strlen(list[d].d_name) + 1));
            ft_strcpy(path_string, dir);
            path_string = ft_strjoin(path_string, "/");
            path_string = ft_strjoin(path_string, list[d].d_name);
            lstat(path_string, &sb);
            free(path_string);
            //lstat(list[d].d_name, &sb);
			
            
            path_string = (char*)malloc(sizeof(char) * (ft_strlen(dir) + ft_strlen(list[d + 1].d_name) + 1));
            ft_strcpy(path_string, dir);
            path_string = ft_strjoin(path_string, "/");
            path_string = ft_strjoin(path_string, list[d + 1].d_name);
            lstat(path_string, &sb2);
            free(path_string);
            //lstat(list[d + 1].d_name, &sb2);
            //lstat(list[d].d_name, &sb);
			//lstat(list[d + 1].d_name, &sb2);
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
