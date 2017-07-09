/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcoetzee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:34:22 by kcoetzee          #+#    #+#             */
/*   Updated: 2017/06/13 15:06:50 by kcoetzee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENT_H
# define ARGUMENT_H

typedef struct  s_argument
{
    char        		*flags;
    int         		field_width;
    int         		precision;
    char        		*length_modifier;
    char        		*conversion_specifier;
    struct s_argument	*next;

}				t_argument;

#endif
