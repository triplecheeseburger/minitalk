/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:55:33 by hakim             #+#    #+#             */
/*   Updated: 2022/01/24 18:55:34 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

static t_stamp	g_stamp;

void	clib_handler(int sig)
{
	static int	bits = 7;
	static int	index = 0;
	static int	count;

	if (sig == SIGUSR2)
	{
		ft_printf("\rACK received: %d", count);
		ft_printf("\nMessage sent successfully.");
		exit(0);
	}
	else
	{
		if (g_stamp.str[index] >> bits & 1)
			kill(g_stamp.pid, SIGUSR1);
		else
			kill(g_stamp.pid, SIGUSR2);
		--bits;
		if (bits == -1)
		{
			bits = 7;
			++index;
		}
		++count;
	}
	ft_printf("\rACK received: %d", count);
}

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					plma;
	int					index;

	index = 0;
	while (str[index] == ' ' || (str[index] >= 9 && str[index] <= 13))
		index++;
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
	if (result > 9223372036854775807 && plma == 1)
		return (-1);
	else if (result > 9223372036854775808ULL && plma == -1)
		return (0);
	return ((int)result * plma);
}

int	main(int ac, char **av)
{
	if (ac != 3)
		return (ft_printf("./client [PID] [MESSAGE]\n"));
	signal(SIGUSR1, clib_handler);
	signal(SIGUSR2, clib_handler);
	g_stamp.pid = ft_atoi(av[1]);
	if (g_stamp.pid < 100 || g_stamp.pid > 100000)
	{
		ft_printf("Wrong PID value received.\n");
		exit(EXIT_FAILURE);
	}
	g_stamp.str = av[2];
	kill(g_stamp.pid, SIGUSR1);
	while (1)
		pause();
	return (0);
}
