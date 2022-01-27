/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:42:08 by hakim             #+#    #+#             */
/*   Updated: 2022/01/24 18:55:29 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	srv_handler(int sig)
{
	static char	byte;
	static char	bits;

	byte *= 2;
	if (sig == SIGUSR1)
		byte += 1;
	bits += 1;
	if (bits == 8)
	{
		if (byte == 0)
			exit(0);
		else
		{
			write(1, &byte, 1);
			bits = 0;
			byte = 0;
		}
	}
}

int	main(void)
{
	ft_printf("pid: %d\n", getpid());
	signal(SIGUSR1, srv_handler);
	signal(SIGUSR2, srv_handler);
	while (1)
		pause();
	return (0);
}
