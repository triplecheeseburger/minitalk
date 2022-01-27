/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:19:06 by hakim             #+#    #+#             */
/*   Updated: 2021/12/21 16:19:08 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	find_conv(const char *format)
{
	char	*conv;
	int		index;
	int		cndex;

	index = 1;
	conv = "cspdiuxX%";
	while (format[index] != '\0')
	{
		cndex = 0;
		while (conv[cndex] != '\0')
			if (format[index] == conv[cndex++])
				return (index);
		++index;
	}
	return (0);
}

t_bool	is_flag(const char *format)
{
	char	*flags;
	int		index;

	index = 0;
	flags = "# +-0";
	while (index < 5)
	{
		if (*format == flags[index])
			return (1);
		++index;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

int	pf_atoi(const char *str, int *outdex)
{
	unsigned long long	result;
	int					plma;
	int					index;

	index = 0;
	plma = 1;
	if (str[index] == '-')
		plma = -1;
	if (str[index] == '-' || str[index] == '+')
		index++;
	result = 0;
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = result * 10 + str[index] - '0';
		index++;
	}
	*outdex += index;
	if (result > 9223372036854775807 && plma == 1)
		return (-1);
	else if (result > 9223372036854775808ULL && plma == -1)
		return (0);
	return ((int)result * plma);
}
