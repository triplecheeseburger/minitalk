/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:34:54 by hakim             #+#    #+#             */
/*   Updated: 2021/12/07 19:49:35 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

# define TRUE 1
# define FALSE -1
# define LOWER 0
# define UPPER 1

typedef char	t_bool;
typedef struct s_opts
{
	t_bool	flags[49];
	t_bool	xcase;
	int		prec;
	int		width;
	int		length;
	char	padd;
	ssize_t	count;
}	t_options;

int		ft_printf(const char *format, ...);
int		f_proc(const char *format, int *index, va_list ap,
			void (*func[])(va_list, t_options *));
int		find_conv(const char *format);
void	write_c(va_list ap, t_options *opts);
void	write_s(va_list	ap, t_options *opts);
void	write_p(va_list ap, t_options *opts);
void	write_d(va_list ap, t_options *opts);
void	write_u(va_list ap, t_options *opts);
void	write_x(va_list ap, t_options *opts);
void	write_5(va_list ap, t_options *opts);
void	get_length_d(int d, t_options *opts);
void	get_length_u(unsigned int u, t_options *opts);
void	get_length_x(unsigned int u, t_options *opts);
void	get_length_s(char *s, t_options *opts);
void	print_integer(int d, t_options *opts);
void	print_uinteger(unsigned int d, t_options *opts);
void	print_hex(unsigned int u, t_options *opts);
void	print_ptr(int index, char *toprint, t_options *opts);
void	ft_putnbr_prec(long long n, t_options *opts);
void	ft_putui_prec(unsigned int u, t_options *opts);
void	ft_putx_prec(unsigned int u, t_options *opts);
void	func_init(void (*func[])(va_list, t_options *));
void	opts_init(t_options *opts);
int		pf_atoi(const char *str, int *outdex);
t_bool	is_flag(const char *format);
size_t	ft_strlen(const char *str);

#endif
