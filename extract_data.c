/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:43:21 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/06/16 14:15:54 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void extract_flags(char *str, char *dest)
{
    int i;
    i = 1;
    while (str[i] && (str[i] == '#' || str[i] == '0' || str[i] == '-' || str[i] == '+' || str[i] == ' '))
    {
        dest[i - 1] = str[i];
        i++;
    }
}

int     extract_field_width(char *str)
{
    // Skips over all characters that are not digits
    int  i;

    i = 0;
    while (str[i] && !isdigit(str[i]))
        i++;
    return (atoi(&str[i]));
}

int     extract_precision(char *str)
{
    int i;

    i = 0;
    // Skip over all characters until the period is found.
    while (str[i] && str[i] != '.')
        i++;
    if (str[i] == '.')
        i++;
    return (atoi(&str[i]));
}

void    extract_length_modifier(char *str, char *dst)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == 'h' || str[i] == 'l' || str[i] == 'j' || str[i] == 'z')
        {
            dst[j] = str[i];
            if ((str[i + 1] == 'h' && str[i] == 'h') || (str[i + 1] == 'l' && str[i] == 'l'))
                dst[j++ + 1] = str[i++ +1];
            j++;
        }
        i++;
    }
}

char    extract_conversion_specifier(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (is_specifier(str[i]))
				return (str[i]);
		i++;
	}
	return (0);
}
