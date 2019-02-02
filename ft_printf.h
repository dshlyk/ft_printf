/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 19:29:22 by sbruen            #+#    #+#             */
/*   Updated: 2019/02/02 18:41:27 by sbruen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

size_t			print_len;
typedef struct	s_mods
{
	int			minus;
	int			plus;
	int			space;
	int			sharp;
	int			zero;
	int			width;
	int			precision;
	int			h;
	int			l;
	int			up_l;
	int			count;
	char		type;
}				t_mods;
void			printer(t_mods *mods, va_list ap);
void			priorities(t_mods *mods, long int num);
void			handle_precision(char *str, t_mods *mods, long int l);
