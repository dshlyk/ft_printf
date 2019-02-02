/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbruen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 17:52:28 by sbruen            #+#    #+#             */
/*   Updated: 2019/02/02 19:20:36 by sbruen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int		count_num(long int n)
{
	int	i;
	
	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*new_fill_str(size_t size, char c)
{
	char	*str;
	
	str = (char *)malloc(sizeof(*str) * (size + 1));
	if (!str)
		return (NULL);
	ft_memset(str, c , size);
	return (str);
}

int		biggest_num(int w, int p, int n)
{
	if (p >= w && p >= n)
		return (p);
	if (w >= p && w >= n)
		return (w);
	return (n);
}

char	*new_strcpy(char *dst, char *src)
{
	char	*ptr;

	ptr = src;
	while (*src)
		*dst++ = *src++;
	return (ptr);
}

long int	conversion(long int num, t_mods *mods)
{
	num = (mods->l == 0 ? (int)num : num);
	num = (mods->h == 1 ? (short int)num : num);
	num = (mods->h == 2 ? (char)num : num);
	num = (mods->l == 1 ? (long int)num : num);
	num = (mods->l == 2 ? (long long int)num : num);
	num = (mods->up_l ? (long double)num : num);
	return (num);
}

void	handle_precision(char *str, t_mods *mods, long int l)
{
	char	*tmp_sp;
	char	*tmp_z;
	char	*final;
	
	//HANDLE PRECISION
	if (mods->precision > mods->count)
		tmp_z = new_fill_str(mods->precision - mods->count, '0');
	else
		tmp_z = ft_strdup("");
	if (*str == '-')
	{
		tmp_z = ft_strjoin("-", tmp_z);
		if (mods->width > mods->precision)
			mods->width--;
		str++;
	}
	
	//HANDLE WIDTH
	if (mods->width > mods->precision && mods->width > mods->count)
	{
		if (mods->precision > mods->count)
			tmp_sp = new_fill_str(mods->width - mods->precision, ' ');
		else
			tmp_sp = new_fill_str(mods->width - mods->count, ' ');
		if (*str == '-')
		{
			if (mods->width > mods->precision)
				*(tmp_sp + ft_strlen(tmp_sp) - 1) = '-';
			else
				tmp_sp = ft_strjoin(tmp_sp, "-");
			str++;
		}
	}
	else
		tmp_sp = ft_strdup("");
	
	//HANDLE ZERO
	if (mods->zero)
	{
		if (mods->width > mods->precision && mods->width > mods->count)
			tmp_sp = (char *)ft_memset((char *)tmp_sp, 48, ft_strlen(tmp_sp));
	}

	//HANDLE PLUS
	if (mods->plus && l >=0)
	{
		if (mods->width > mods->precision && mods->width > mods->count)
		{
			if (mods->minus)
			{
				tmp_z = ft_strjoin("+", tmp_z);
				*(tmp_sp + ft_strlen(tmp_sp) - 1) = '\0';
			}
			else
			{
				if (mods->zero)
					*tmp_sp = '+';
				else
					*(tmp_sp + ft_strlen(tmp_sp) - 1) = '+';
			}
		}
		else if (mods->precision >= mods->width && mods->precision > mods->count)
			tmp_z = ft_strjoin("+", tmp_z);
		else
			str = ft_strjoin("+", str);
	}

	//HANDLE SPACE
	if (mods->space)
	{
		if (mods->precision > mods->width && mods->precision > mods->count)
			tmp_z = ft_strjoin(" ", tmp_z);
		if (mods->width > mods->precision && mods->width > mods->count && mods->minus)
		{
			tmp_z = ft_strjoin(" ", tmp_z);
			*(tmp_sp + ft_strlen(tmp_sp) - 1) = '\0';
		}
		else
			*tmp_sp = ' ';
	}
		
	//HANDLE MINUS
	if (mods->zero)
	{
		final = ft_strjoin(tmp_z, tmp_sp);
		final = ft_strjoin(final, str);
	}
	else
	{
		final = ft_strjoin(tmp_z, str);
		if (mods->minus)
			final = ft_strjoin(final, tmp_sp);
		else
			final = ft_strjoin(tmp_sp, final);
	}
	ft_putstr(final);
	print_len += ft_strlen(final);
}

void	printer(t_mods *mods, va_list ap)
{
	long int			l;
	int					count;
	char				*str;
	char				*tmp;

	if (mods->type == 'd' || mods->type == 'i')
	{
		l = va_arg(ap, long int);
		l = conversion(l, mods);
		mods->count = count_num(l);
		priorities(mods, l);
		if (l == 0 && mods->precision == 0)
			str = ft_strdup("");
		else
			str = ft_itoa(l);
		handle_precision(str, mods, l);
	}
}
