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

void	send_bytes(pid_t spid, char letter)
{
	int	bits;

	bits = 8;
	while (bits--)
	{
		if (letter >> bits & 1)
			kill(spid, SIGUSR1);
		else
			kill(spid, SIGUSR2);
		usleep(40);
	}
}

void	send_msg(pid_t spid, char *msg)
{
	int	i;

	i = 0;
	while (msg[i] != '\0')
	{
		send_bytes(spid, msg[i]);
		++i;
	}
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
	pid_t	spid;

	if (ac != 3)
		return (ft_printf("./client [PID] [MESSAGE]\n"));
	spid = ft_atoi(av[1]);
	send_msg(spid, av[2]);
	return (0);
}
