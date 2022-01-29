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

void	srvb_handler(int sig, siginfo_t *siginfo, void *context)
{
	static char		byte = -1;
	static char		bits;
	static pid_t	cpid;

	(void)context;
	if (byte == -1)
	{
		cpid = siginfo->si_pid;
		return ((void)(byte++ && kill(siginfo->si_pid, SIGUSR1)));
	}
	byte = byte << 1 | (sig == SIGUSR1);
	++bits;
	if (bits == 8)
	{
		if (byte == 0 && write(1, "\n", 1) && --byte)
			kill(cpid, SIGUSR2);
		else
		{
			write(1, &byte, 1);
			byte = 0;
		}
		bits = 0;
	}
	kill(cpid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sigact;

	ft_printf("pid: %d\n", getpid());
	sigact.sa_sigaction = srvb_handler;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, 0);
	sigaction(SIGUSR2, &sigact, 0);
	while (1)
		pause();
	return (0);
}
