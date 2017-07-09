/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:40:46 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/06/13 15:15:29 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argument.h"
#include <stdlib.h>
#include <stdarg.h>

t_argument  *add_argument(t_argument *list, char *f, int fw, int prec, char *lm, char *cs)
{
    t_argument *argument;

    argument = (t_argument*)malloc(sizeof(t_argument));
    if (!argument)
        return (NULL);
    argument->next = list;
    argument->flags = f;
    argument->field_width = fw;
    argument->precision = prec;
    argument->length_modifier = lm;
    argument->conversion_specifier = cs;
    return (argument);
}
