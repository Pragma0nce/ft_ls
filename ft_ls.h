#ifndef      H_FT_LS
# define    H_FT_LS

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "libft.h"

typedef struct  s_option
{
    char                option;
    struct  s_option    *next;
}               t_option; 

typedef struct  s_path
{
    char    *path_name;
    struct s_path *next;
}               t_path;

// PARAM_LONG
void    print_permissions(mode_t mode);
void    print_stats(struct stat sb);
void    display_long_format(struct dirent *list, int size);

// UTILITY
void    sort_list(struct dirent *list, int size);

// PARAMETER PARSING
t_option    *add_option(char opt, t_option *list);
t_path      *add_path(char *path_name, t_path *list);

void        print_paths(t_path *path);
void        print_options(t_option *list);
// MAIN
void    display_default(struct dirent *list, int size);

#endif
