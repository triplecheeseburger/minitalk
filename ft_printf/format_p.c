/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 04:05:52 by hakim             #+#    #+#             */
/*   Updated: 2021/12/27 04:05:55 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_p(va_list ap, t_options *opts)
{
	unsigned long long	ptr;
	int					index;
	char				toprint[16];

	ptr = va_arg(ap, long long);
	if (opts->flags['+'] == 1)
		opts->count += write(1, "+", 1);
	else if (opts->flags[' '] == 1)
		opts->count += write(1, " ", 1);
	opts->width -= (int)opts->count;
	index = 16;
	while (--index >= 0)
	{
		toprint[index] = "0123456789abcdef"[ptr % 16];
		ptr /= 16;
	}
	while (++index < 16 && toprint[index] == '0')
		;
	print_ptr(index, toprint, opts);
}

void	print_ptr(int index, char *toprint, t_options *opts)
{
	int	printed;

	if (index == 16)
		index = 15;
	if (opts->flags['-'] == FALSE)
	{
		while (opts->width-- > 16 - index + 2)
			opts->count += write(1, " ", 1);
		write(1, "0x", 2);
		opts->count += 2;
		while (index < 16)
			opts->count += write(1, &toprint[index++], 1);
	}
	else if (opts->flags['-'] == TRUE)
	{
		write(1, "0x", 2);
		opts->count += 2;
		while (index < 16)
			opts->count += write(1, &toprint[index++], 1);
		printed = (int)opts->count;
		while (opts->width-- > printed)
			opts->count += write(1, " ", 1);
	}
}
