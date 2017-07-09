/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 12:40:18 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/07/09 12:53:43 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_permissions(mode_t mode)
{
	char type;

	type = '-';
	if (S_ISDIR(mode))
		type = 'd';
	else if (S_ISLNK(mode))
		type = 'l';
	else if (S_ISCHR(mode))
		type = 'c';
	else if (S_ISBLK(mode))
		type = 'b';
	else if (S_ISSOCK(mode))
		type = 's';
	else if (S_ISFIFO(mode))
		type = 'p';
	printf("%c", type);
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

void	print_stats(struct stat sb)
{
	char			*time;
	struct passwd	*pwd;
	struct group	*grp;

	pwd = getpwuid(sb.st_uid);
	grp = getgrgid(sb.st_gid);
	time = ctime(&sb.st_mtime);
	time[ft_strlen(time) - 1] = '\0';
	print_permissions(sb.st_mode);
	printf(" %ld ", sb.st_nlink);
	printf("%s \t", pwd->pw_name);
	printf("%s \t", grp->gr_name);
	if (S_ISCHR(sb.st_mode) || S_ISBLK(sb.st_mode))
		printf("%u, %u\t", MAJOR(sb.st_rdev), MINOR(sb.st_rdev));
	else
		printf("%ld \t", sb.st_size);
	printf("%s ", time);
}

int		get_block_total(struct dirent *list, int size,
							t_format *format, char *dir)
{
	int			i;
	struct stat	sb;
	int			block_size;
	char		*path_string;

	i = 0;
	block_size = 0;
	while (i < size)
	{
		path_string = (char*)malloc(sizeof(char) *
				(ft_strlen(dir) + ft_strlen(list[i].d_name) + 1));
		ft_strcpy(path_string, dir);
		path_string = ft_strjoin(path_string, "/");
		path_string = ft_strjoin(path_string, list[i].d_name);
		lstat(path_string, &sb);
		if ((list[i].d_name[0] == '.' && format->has_a) ||
				(list[i].d_name[0] != '.'))
			block_size += sb.st_blocks;
		free(path_string);
		i++;
	}
	return (block_size);
}

void	path_join(char **path_string, char *dir, struct dirent *list, int i)
{
	*path_string = (char*)malloc(sizeof(char) * (ft_strlen(dir) + ft_strlen(list[i].d_name) + 1));
	ft_strcpy(*path_string, dir);
	*path_string = ft_strjoin(*path_string, "/");
	*path_string = ft_strjoin(*path_string, list[i].d_name);
}

void	display_long_format(struct dirent *list, int size, t_format *format, char *dir)
{
	int			i;
	struct stat	sb;
	char		*path_string;
	char		buffer[255];
	int			fill;

	i = 0;
	lstat(list[0].d_name, &sb);
	printf("total: %d\n", get_block_total(list, size, format, dir));
	while (i < size)
	{
		path_join(&path_string, dir, list, i);
		lstat(path_string, &sb);
		if ((list[i].d_name[0] == '.' && format->has_a) || (list[i].d_name[0] != '.'))
		{
			print_stats(sb);
			printf("%s", list[i].d_name);
			if (S_ISLNK(sb.st_mode))
			{
				fill = readlink(path_string, buffer, 255);
				buffer[fill] = '\0';
				printf(" -> %s", buffer);
			}
			printf("\n");
		};
		i++;
		free(path_string);
	}
	printf("\n");
}



