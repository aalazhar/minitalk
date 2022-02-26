/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mi_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalazhar <aalazhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:11:13 by aalazhar          #+#    #+#             */
/*   Updated: 2022/01/16 17:26:47 by aalazhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mi_utils.h"

void	reset(int *i, char *byte, pid_t *new_pid, pid_t *cur_pid)
{
	*i = 0;
	*byte = 0;
	*new_pid = *cur_pid;
}

char	unshift(int *sig, char *byte, int *i)
{
	if (*sig == SIGUSR1)
	{
		*byte = *byte | (128 >> *i);
		(*i)++;
	}
	else
		(*i)++;
	return (*byte);
}

void	get_msg(int sig, siginfo_t *info, void *ptr)
{
	static char		byte;
	static int		i;
	static pid_t	new_pid;
	static pid_t	cur_pid;

	(void)ptr;
	if (!new_pid)
		new_pid = info->si_pid;
	cur_pid = info->si_pid;
	if (cur_pid != new_pid)
		reset(&i, &byte, &new_pid, &cur_pid);
	byte = unshift(&sig, &byte, &i);
	if (i == 8)
	{
		write (1, &byte, 1);
		i = 0;
		byte = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sig;

	pid = getpid();
	sig.sa_sigaction = get_msg;
	sig.sa_flags = SA_SIGINFO;
	ft_putstr("PID : ");
	ft_putnbr(pid);
	ft_putchar('\n');
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause ();
	return (0);
}
