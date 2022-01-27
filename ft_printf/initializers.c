/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:23:00 by hakim             #+#    #+#             */
/*   Updated: 2021/12/21 16:23:02 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	opts_init(t_options *opts)
{
	opts->flags['#'] = FALSE;
	opts->flags[' '] = FALSE;
	opts->flags['+'] = FALSE;
	opts->flags['-'] = FALSE;
	opts->flags['0'] = FALSE;
	opts->xcase = LOWER;
	opts->prec = FALSE;
	opts->width = FALSE;
	opts->padd = ' ';
	opts->length = 0;
	opts->count = 0;
}

void	func_init(void (*func[])(va_list, t_options *))
{
	func['c'] = write_c;
	func['s'] = write_s;
	func['p'] = write_p;
	func['d'] = write_d;
	func['i'] = write_d;
	func['u'] = write_u;
	func['x'] = write_x;
	func['X'] = write_x;
	func['%'] = write_5;
}
