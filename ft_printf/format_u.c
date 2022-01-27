/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 02:27:36 by hakim             #+#    #+#             */
/*   Updated: 2021/12/28 02:27:39 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_u(va_list ap, t_options *opts)
{
	unsigned int	u;

	u = va_arg(ap, int);
	if (u == 0 && opts->prec == 0)
	{
		while (opts->width--)
			opts->count += write(1, " ", 1);
		return ;
	}
	get_length_u(u, opts);
	print_uinteger(u, opts);
}

void	get_length_u(unsigned int u, t_options *opts)
{
	if (u == 0)
		opts->length = 1;
	while (u && ++opts->length)
		u /= 10;
}

void	print_uinteger(unsigned int u, t_options *opts)
{
	if (opts->flags['-'] == FALSE)
	{
		while (opts->width > opts->length && opts->width-- > opts->prec)
			opts->count += write(1, &opts->padd, 1);
		ft_putui_prec(u, opts);
	}
	else if (opts->flags['-'] == TRUE)
	{
		ft_putui_prec(u, opts);
		while (opts->width-- > opts->length)
			opts->count += write(1, " ", 1);
	}
}

void	ft_putui_prec(unsigned int u, t_options *opts)
{
	char	a[10];
	int		i;

	i = 10;
	while (opts->prec > opts->length && ++opts->length)
		opts->count += write(1, "0", 1);
	if (u == 0)
		opts->count += write(1, "0", 1);
	while (u)
	{
		a[--i] = u % 10 + '0';
		u /= 10;
	}
	opts->count += write(1, &a[i], 10 - i);
}
