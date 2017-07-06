#include "ft_ls.h"

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

void    print_stats(struct stat sb)
{
    char *time;
    struct passwd *pwd;
    struct group *grp;

    pwd = getpwuid(sb.st_uid);          // Init
    grp = getgrgid(sb.st_gid);
    time = ctime(&sb.st_mtime);
    time[ft_strlen(time) - 1] = '\0';
    
    print_permissions(sb.st_mode);      // Print the permission modes
    printf("%ld ", sb.st_nlink);        // Print the number of links
    printf("%s \t", pwd->pw_name);      // Print the user name
    printf("%s \t", grp->gr_name);      // Print the group name
    printf("%ld \t", sb.st_size);       // Print the size in KB's
    printf("%s ", time);                // Print the last time modified
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
            printf(" ");
            print_stats(sb);
            printf("%s ", list[i].d_name);
        }
        printf("\n");
        i++;
    }
    printf("\n");
}



