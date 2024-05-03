/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:17:02 by codespace         #+#    #+#             */
/*   Updated: 2024/01/09 16:46:07 by bapasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static char	*g_line = NULL;

void	print_banner(void)
{
	ft_putstr_fd("=========================================\n", 1);
	ft_putstr_fd("• ▌ ▄ ·. ▪   ▐ ▄ ▪  ▄▄▄▄▄ ▄▄▄· ▄▄▌  ▄ •▄\n", 1);
	ft_putstr_fd("·██ ▐███▪██ •█▌▐███ •██  ▐█ ▀█ ██•  █▌▄▌▪\n", 1);
	ft_putstr_fd("▐█ ▌▐▌▐█·▐█·▐█▐▐▌▐█· ▐█.▪▄█▀▀█ ██ ▪ ▐▀▀▄·\n", 1);
	ft_putstr_fd("██ ██▌▐█▌▐█▌██▐█▌▐█▌ ▐█▌·▐█▪ ▐▌▐█▌ ▄▐█.█▌\n", 1);
	ft_putstr_fd("▀▀  █▪▀▀▀▀▀▀▀▀ █▪▀▀▀ ▀▀▀  ▀  ▀ .▀▀▀ ·▀  ▀\n", 1);
	ft_putstr_fd("=========================================\n", 1);
	ft_putstr_fd("	       PID : \e[1;32m", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\e[1;37m\n\n", 1);
	ft_putstr_fd("\e[1;37m> Messages :\n\n\e[0;37m", 1);
}

char	*ft_join(char *src1, char src2)
{
	char	*result;
	int		len_src1;
	int		c;

	len_src1 = ft_strlen(src1);
	result = (char *)malloc(sizeof(*result) * (len_src1 + 2));
	if (result == NULL)
		return (NULL);
	c = 0;
	while (c < len_src1)
	{
		result[c] = src1[c];
		c++;
	}
	result[c++] = src2;
	result[c] = '\0';
	free(src1);
	return (result);
}

void	binary_to_ascii(const char *binary, pid_t sender_pid)
{
	int	decimal;
	int	base;
	int	i;

	decimal = 0;
	base = 1;
	i = 7;
	while (i >= 0)
	{
		if (binary[i] == '1')
			decimal += base;
		base *= 2;
		i--;
	}
	if ((char)decimal == 0)
	{
		ft_putstr_fd(g_line, 1);
		if (decimal == 0)
			ft_putchar_fd('\n', 1);
		kill(sender_pid, SIGUSR1);
		free(g_line);
		g_line = NULL;
	}
	g_line = ft_join(g_line, (char)decimal);
}

void	signal_handler(int signalNum, siginfo_t *info, void *context)
{
	static char	*character;
	static int	i = 0;

	(void)context;
	if (character == NULL)
	{
		character = malloc(8);
		if (character == NULL)
			return ;
	}
	if (i < 8)
	{
		if (signalNum == SIGUSR1)
			character[i] = '1';
		else if (signalNum == SIGUSR2)
			character[i] = '0';
		i++;
		if (i == 8)
		{
			binary_to_ascii(character, info->si_pid);
			free(character);
			character = NULL;
			i = 0;
		}
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	print_banner();
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
