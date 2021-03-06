/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 17:35:40 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/07/09 17:43:55 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdbool.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include "libft.h"

# define TRUE 1
# define FALSE 0
# define BOOL int

# define MINORBITS 20
# define MINORMASK ((1U << MINORBITS) - 1)
# define ft_printf printf
# define MAJOR(dev) ((unsigned int) ((dev) >> MINORBITS))
# define MINOR(dev) ((unsigned int) ((dev) & MINORMASK))

typedef struct	s_format
{
	BOOL has_a;
	BOOL has_l;
	BOOL has_r;
	BOOL has_t;
}				t_format;

typedef struct	s_option
{
	char				option;
	struct s_option		*next;
}				t_option;

typedef struct	s_path
{
	char			*path_name;
	struct s_path	*next;
}				t_path;

typedef struct	s_file
{
	struct dirent data;
	struct s_file *next;
}				t_file;

typedef struct	s_directory
{
	char	*path;
	int		path_len;
	int		max_len;
}				t_directory;

void			set_path(t_directory *dir, char *str);
void			push_path(t_directory *dir, char *str);
void			pop_path(t_directory *dir);

void			sort_by_time_reversed(struct dirent *list, int size, char *dir);
void			sort_by_time(struct dirent *list, int size, char *dir);
void			print_permissions(mode_t mode);
void			print_stats(struct stat sb);
void			display_long_format(struct dirent *list, int size,
				t_format *format, char *dir);
void			display_all(struct dirent *list, int size);
int				get_block_total(struct dirent *list, int size,
				t_format *format, char *dir);
void			sort_list(struct dirent *list, int size);
void			sort_list_reverse(struct dirent *list, int size);
struct dirent	*load_list(char *directory_path, int *files_loaded);
t_format		*set_format(BOOL a, BOOL l, BOOL r, BOOL t);
int				get_path_length(t_path *path);
void			parse_parameters(int argc, char **argv);
void			swap(struct dirent list[], int index);
t_file			*add_file(struct dirent data, t_file *list);
void			recursive_loop(struct dirent *list, t_directory *directories,
				int len, t_format *format);
t_option		*add_option(char opt, t_option *list);
t_path			*add_path(char *path_name, t_path *list);
void			select_mode(t_option *option, t_path *path);
void			print_paths(t_path *path);
void			print_options(t_option *list);
void			display_default(char *dir, t_format *format);
void			display_recursive(char *dir, t_format *format);
#endif
