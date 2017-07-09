/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 13:42:35 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/06/16 14:15:51 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*convert_to_base(unsigned int num, int base)
{
	unsigned int q;
	unsigned int remainder;
	int i;
	char *result;

	result = ft_strnew(50);
	while (q != 0)
	{
		remainder = q % base;
		if (re
	}	
}
