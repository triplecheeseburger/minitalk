/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_x0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:37:22 by hakim             #+#    #+#             */
/*   Updated: 2021/12/07 13:29:11 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_x(va_list ap, t_options *opts)
{
	unsigned int	u;

	u = va_arg(ap, int);
	if (u == 0 && opts->prec == 0)
	{
		while (opts->width--)
			opts->count += write(1, " ", 1);
		return ;
	}
	get_length_x(u, opts);
	print_hex(u, opts);
}

void	get_length_x(unsigned int u, t_options *opts)
{
	if (u == 0)
		opts->length = 1;
	if (opts->flags['#'] == TRUE)
	{
		opts->length += 2;
		opts->prec += 2;
	}
	while (u && ++opts->length)
		u = u / 16;
}

void	print_hex(unsigned int u, t_options *opts)
{
	if (opts->flags['-'] == FALSE)
	{
		while (opts->width > opts->length && opts->width-- > opts->prec)
			opts->count += write(1, &opts->padd, 1);
		ft_putx_prec(u, opts);
	}
	else if (opts->flags['-'] == TRUE)
	{
		ft_putx_prec(u, opts);
		while (opts->width-- > opts->length)
			opts->count += write(1, " ", 1);
	}
}

void	ft_putx_prec(unsigned int u, t_options *opts)
{
	char	a[8];
	char	*hex;
	int		i;

	if (opts->xcase == LOWER && opts->flags['#'] == 1 && u != 0)
		opts->count += write(1, "0x", 2);
	else if (opts->xcase == UPPER && opts->flags['#'] == 1 && u != 0)
		opts->count += write(1, "0X", 2);
	i = 8;
	while (opts->prec > opts->length && ++opts->length)
		opts->count += write(1, "0", 1);
	if (u == 0)
		opts->count += write(1, "0", 1);
	if (opts->xcase == LOWER)
		hex = "0123456789abcdef";
	else if (opts->xcase == UPPER)
		hex = "0123456789ABCDEF";
	while (u)
	{
		a[--i] = hex[u % 16];
		u /= 16;
	}
	opts->count += write(1, &a[i], 8 - i);
}
