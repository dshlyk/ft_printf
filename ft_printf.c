/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:52:38 by sbruen            #+#    #+#             */
/*   Updated: 2019/02/02 19:20:38 by sbruen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>

void	pars_flags(char *str, t_mods *mods)
{
	if (*str == '-')
		mods->minus = 1;
	else if (*str == '+')
		mods->plus = 1;
	else if (*str == ' ')
		mods->space = 1;
	else if (*str == '#')
		mods->sharp = 1;
	else if (*str == '0')
		mods->zero = 1;
}

int		num_counter(long int num)
{
	int		i;

	i = 0;
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

int		pars_width(char *str, t_mods *mods)
{
	int		i;

	mods->width = ft_atoi(str);
	i = num_counter(mods->width);
	return (i);
}

int		pars_precision(char *str, t_mods *mods)
{
	int		i;

	mods->precision = ft_atoi(str);
	i = num_counter(mods->precision);
	return (i);
}

void	pars_length(char *str, t_mods *mods)
{
	if (*str == 'h')
	{
		mods->l = 0;
		mods->up_l = 0;
		if (mods->h > 1)
			return ;
		mods->h = mods->h + 1;
	}
	if (*str == 'l')
	{
		mods->h = 0;
		mods->up_l = 0;
		if (mods->l > 1)
			return ;
		mods->l = mods->l + 1;
	}
	if (*str == 'L')
	{
		mods->h = 0;
		mods->l = 0;
		if (mods->up_l > 0)
			return ;
		mods->up_l = 1;
	}
}

void	init_list(t_mods *mods)
{
	mods->minus = 0;
	mods->plus = 0;
	mods->space = 0;
	mods->sharp = 0;
	mods->zero = 0;
	mods->width = 0;
	mods->precision = -1;
	mods->h = 0;
	mods->l = 0;
	mods->up_l = 0;
	mods->count = 0;
	mods->type = 0;
}

int		my_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

void	priorities(t_mods *mods, long int num)
{
	if (mods->space)
		if (mods->plus || num < 0)
			mods->space = 0;
	if (mods->zero)
		if (mods->minus || mods->precision >= 0)
			mods->zero = 0;
	if (num == 0 && mods->precision == 0)
	{
		mods->zero = 0;
		mods->count = 0;
	}
}

char	*parser(t_mods *mods, char *p, va_list ap)
{
	int		i;
	
	while (*p)
	{
		if (*p == '%')
		{
			init_list(mods);
			p++;
		}
		else if (my_strchr("-+ #", *p))
		{
			pars_flags(p, mods);
			p++;
		}
		else if (*p == '0')
		{
			mods->zero = 1;
			p++;
		}
		else if (ft_isdigit(*p))
		{
			i = pars_width(p, mods);
			p += i;
		}
		else if (*p == '.')
		{
			p++;
			if (ft_isdigit(*p))
			{	
				while (*p == '0')
					p++;
				i = pars_precision(p, mods);
				p += i;
			}
			else
				mods->precision = 0;
		}
		else if (*p == 'h' || *p == 'l' || *p == 'L')
		{
			pars_length(p, mods);
			p++;
		}
		else if (my_strchr("diuoxXfFeEgGaAcsSpn%", *p))
		{
			mods->type = *p;
			printer(mods, ap);
			break ;
		}
		else
		{
			mods->count = 1;
			mods->plus = 0;
			handle_precision(ft_strdup(""), mods, 0);
			while (*p != '%' && *p)
			{
				ft_putchar(*p);
				p++;
				print_len++;
			}
		}
	}
	return (p);
}
int		ft_printf(char *format, ...)
{
	va_list	aptr;
	char	*p;
	t_mods	*mods;
	
	mods = (t_mods *)malloc(sizeof(t_mods));
	va_start(aptr, format);
	print_len = 0;
	p = format;
	while(*p)
	{
		if (*p == '%')
			p = parser(mods, p, aptr);
		else
		{
			ft_putchar(*p);
			print_len++;
		}
		p++;
	}
	va_end(aptr);
	return (print_len);
}
/*
int		main(void)
{
	int		a;
	int		b;

	a = ft_printf("M:%-+3.4d\n", -3456);
	b = printf("L:%-+3.4d\n", -3456);
	printf("MY=%d LB=%d\n", a, b);
}*/
