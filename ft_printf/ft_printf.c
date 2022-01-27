/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:17:19 by hakim             #+#    #+#             */
/*   Updated: 2021/12/07 19:48:39 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		index;
	void	(*func[128])(va_list, t_options *);

	if (format == 0)
		return (-1);
	count = 0;
	index = 0;
	va_start(ap, format);
	func_init(func);
	while (format[index] != '\0')
	{
		if (format[index] != '%' && ++count)
			write(1, &format[index++], 1);
		else
			count += f_proc(format, &index, ap, func);
	}
	va_end(ap);
	return (count);
}

int	f_proc(const char *format, int *index, va_list ap,
			void (*func[])(va_list, t_options *))
{
	t_options	opts;
	int			conv;
	int			opdex;

	conv = *index + find_conv(&format[*index]);
	opts_init(&opts);
	opdex = *index;
	while (++opdex < conv && is_flag(&format[++(*index)]))
		opts.flags[(int)format[*index]] = TRUE;
	opts.width = pf_atoi(&format[*index], index);
	if (format[(*index)++] == '.')
	{
		opts.flags['.'] = TRUE;
		opts.prec = pf_atoi(&format[*index], index);
	}
	if (opts.flags['0'] == TRUE && opts.prec == FALSE)
		opts.padd = '0';
	if (format[conv] == 'X')
		opts.xcase = UPPER;
	func[(int)format[conv]](ap, &opts);
	*index = conv + 1;
	return ((int)opts.count);
}
