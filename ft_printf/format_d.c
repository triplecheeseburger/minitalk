/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_du.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:36:30 by hakim             #+#    #+#             */
/*   Updated: 2021/12/07 13:28:44 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	write_d(va_list ap, t_options *opts)
{
	int	d;

	d = va_arg(ap, int);
	if (d == 0 && opts->prec == 0)
	{
		while (opts->width--)
			opts->count += write(1, " ", 1);
		return ;
	}
	get_length_d(d, opts);
	print_integer(d, opts);
}

void	get_length_d(int d, t_options *opts)
{
	if (d == 0)
		opts->length = 1;
	if (d < 0 || opts->flags['+'] == TRUE || opts->flags[' '] == TRUE)
		++opts->length;
	while (d && ++opts->length)
		d /= 10;
}

void	print_integer(int d, t_options *opts)
{
	if (opts->flags['-'] == FALSE)
	{
		if (d < 0 && opts->padd == '0' && opts->width > opts->prec)
			opts->prec = --opts->width;
		if (d < 0 && opts->prec > opts->length && opts->width > opts->prec)
			--opts->width;
		while (opts->width > opts->length && opts->width-- > opts->prec)
			opts->count += write(1, &opts->padd, 1);
		ft_putnbr_prec((long long)d, opts);
	}
	else if (opts->flags['-'] == TRUE)
	{
		ft_putnbr_prec((long long)d, opts);
		while (opts->width-- > opts->length)
			opts->count += write(1, " ", 1);
	}
}

void	ft_putnbr_prec(long long n, t_options *opts)
{
	char	a[10];
	int		i;

	if (n >= 0 && opts->flags['+'] == 1)
		opts->count += write(1, "+", 1);
	else if (n >= 0 && opts->flags[' '] == 1)
		opts->count += write(1, " ", 1);
	i = 10;
	opts->prec += n < 0;
	if (n < 0)
	{
		opts->count += write(1, "-", 1);
		n = -n;
	}
	while (opts->prec > opts->length && ++opts->length)
		opts->count += write(1, "0", 1);
	if (n == 0)
		opts->count += write(1, "0", 1);
	while (n)
	{
		a[--i] = n % 10 + '0';
		n /= 10;
	}
	opts->count += write(1, &a[i], 10 - i);
}
