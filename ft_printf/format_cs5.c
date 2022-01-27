/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_csp5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:35:12 by hakim             #+#    #+#             */
/*   Updated: 2021/12/07 13:27:55 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_c(va_list ap, t_options *opts)
{
	char	c;

	c = va_arg(ap, int);
	if (opts->flags['-'] == FALSE)
	{
		while (opts->width-- > 1)
			opts->count += write(1, " ", 1);
		opts->count += write(1, &c, 1);
	}
	else if (opts->flags['-'] == TRUE)
	{
		opts->count += write(1, &c, 1);
		while (opts->width-- > 1)
			opts->count += write(1, " ", 1);
	}
}

void	write_s(va_list ap, t_options *opts)
{
	char	*s;

	s = va_arg(ap, char *);
	if (s == 0)
		s = "(null)";
	get_length_s(s, opts);
	if (opts->flags['-'] == FALSE)
	{
		while (opts->width-- > opts->length)
			opts->count += write(1, " ", 1);
		while (opts->length-- && *s != '\0')
			opts->count += write(1, s++, 1);
	}
	else if (opts->flags['-'] == TRUE)
	{
		while (opts->length-- && *s != '\0')
			opts->count += write(1, s++, 1);
		opts->length += (int)opts->count + 1;
		while (opts->width-- > opts->length)
			opts->count += write(1, " ", 1);
	}
}

void	get_length_s(char *s, t_options *opts)
{
	int	len;

	len = (int)ft_strlen(s);
	if (opts->prec == FALSE)
		opts->length = len;
	else if (opts->width > len && opts->prec > len)
		opts->length = len;
	else
		opts->length = opts->prec;
}

void	write_5(va_list ap, t_options *opts)
{
	if (ap)
		write(1, "", 0);
	opts->count = write(1, "%", 1);
}
