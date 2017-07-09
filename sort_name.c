#include "ft_ls.h"


void	sort_list(struct dirent *list, int size)
{
	int n;
	int c;
	int d;
    int off_1;
    int off_2;
	struct dirent temp;

	n = size;
	c = 0;
	d = 0;
    off_1 = 0;
    off_2 = 0;
	while (c < n - 1)
	{
		d = 0;
		while (d < n - c - 1)
		{
            off_1 = 0;
            off_2 = 0;
            if (list[d].d_name[0] == '.' || list[d].d_name[0] == '\\')
                off_1 = 1;
            if (list[d + 1].d_name[0] == '.' || list[d].d_name[0] == '\\')
                off_2 = 1;
			if (ft_strcmp(&(list[d].d_name[off_1]), &(list[d + 1].d_name[off_2])) > 0)
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


void	sort_list_reverse(struct dirent *list, int size)
{
	int n;
	int c;
	int d;
    int off_1;
    int off_2;
	struct dirent temp;

	n = size;
	c = 0;
	d = 0;
	while (c < n - 1)
	{
		d = 0;
		while (d < n - c - 1)
		{
            off_1 = 0;
            off_2 = 0;
            if (list[d].d_name[0] == '.' || list[d].d_name[0] == '\\')
                off_1 = 1;
            if (list[d + 1].d_name[0] == '.' || list[d].d_name[0] == '\\')
                off_2 = 1;
			if (ft_strcmp(&(list[d].d_name[off_1]), &(list[d + 1].d_name[off_2])) < 0)
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
