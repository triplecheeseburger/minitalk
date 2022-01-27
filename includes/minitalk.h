/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:41:28 by hakim             #+#    #+#             */
/*   Updated: 2022/01/24 18:41:30 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "ft_printf.h"

typedef struct s_stamp
{
	char	*str;
	pid_t	pid;
}	t_stamp;

void	send_bytes(pid_t spid, char letter);
void	send_msg(pid_t spid, char *msg);
void	srv_handler(int sig);
void	srvb_handler(int sig, siginfo_t *siginfo, void *context);
void	clib_handler(int sig);
int		ft_atoi(const char *str);

#endif
