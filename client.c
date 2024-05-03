/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:12:56 by codespace         #+#    #+#             */
/*   Updated: 2024/01/08 19:07:05 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	int	pid;

	i = 0;
	j = 0;
	if (argc != 3)
		ft_print_error(0);
	pid = atoi(argv[1]);
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
		send_signal(pid, argv[2][j]);
		j++;
	}
	send_signal(pid, '\0');
	return (0);
}
