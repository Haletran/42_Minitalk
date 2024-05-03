/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:16:41 by codespace         #+#    #+#             */
/*   Updated: 2024/01/08 19:06:53 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	send_signal(int pid, unsigned char character)
{
	int				i;
	unsigned char	tmp;

	i = 8;
	tmp = character;
	while (i > 0)
	{
		i--;
		tmp = character >> i;
		if (tmp % 2)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(600);
	}
}

void	signal_handler(int signalNum)
{
	if (signalNum == SIGUSR1)
		ft_putstr_fd("\e[1;32mMessage Received\e[1;37m\n", 1);
}

void	ft_print_error(int error)
{
	if (error == 0)
		ft_putstr_fd("\033[1;31mError\033[0m : Invalid Usage\n", 1);
	if (error == 1)
		ft_putstr_fd("\033[1;31mError\033[0m : Invalid PID\n", 1);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (argc != 3)
		ft_print_error(0);
	signal(SIGUSR1, signal_handler);
	while (i < (int)ft_strlen(argv[1]))
	{
		if (!ft_isdigit(argv[1][i++]))
			ft_print_error(1);
	}
	i = 0;
	while (argv[2][i])
		i++;
	while (i > j)
	{
		send_signal(atoi(argv[1]), argv[2][j]);
		j++;
	}
	send_signal(atoi(argv[1]), '\0');
	return (0);
}
