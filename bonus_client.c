/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalazhar <aalazhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:20:35 by aalazhar          #+#    #+#             */
/*   Updated: 2022/01/16 18:00:27 by aalazhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mi_utils.h"

void	handler(int sig)
{
	if (sig == SIGUSR1)
		ft_putstr("SUCCEFULLY RECEIVED !!\n");
}

void	msg_shift(char c, pid_t pid)
{
	int	i;
	int	bit;

	i = 0;
	bit = 0;
	while (bit < 8)
	{
		if (c & 128)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c <<= 1;
		bit++;
		usleep(800);
	}
}

void	send_msg(char *msg, pid_t pid)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		msg_shift(msg[i], pid);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR2);
		usleep(500);
		i++;
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (kill(pid, 0) < 0 || pid <= 0)
			ft_putstr("Error : INVALID PID .....\n");
		else
		{
			ft_putstr("Sending .....\n");
			signal(SIGUSR1, handler);
			send_msg(av[2], pid);
			return (0);
		}
	}
	else
		ft_putstr("Error : INVALID ARGUMANTS .....");
	return (0);
}
