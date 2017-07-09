/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 11:01:37 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/06/16 14:15:52 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"

void	process_conversion(char converter, char *output, int value)
{
	char *ptr;
	if (converter == 'd')
	{
		ptr = ft_itoa(value);
		ft_strcat(output, ptr);	
	}
	else if (converter == 'o')
	{
		
	}
	//printf("OUTPUT: %s\n", ptr);
}

void	process_flags(char *flags, char converter,  char *output)
{
	int i;

	i = 0;
	while (flags[i])
	{
		if (flags[i] == '#')
		{
			if (converter == 'o')
				output[0] = '0';
			else if (converter == 'x' || converter == 'X')
				output[1] = converter;
		}
		i++;
	}
}
