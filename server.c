/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:09:32 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/04 17:59:14 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft/libft.h"

int	main(void)
{
	struct sigaction	signal;

	print_pid();
	signal.sa_flags = SA_RESTART | SA_SIGINFO;
	signal.sa_sigaction = &client_signal_handler;
	if (sigaction(SIGUSR1, &signal, NULL) == -1)
		ft_putstr_fd("ERROR USING SIGUSR1\n", 1);
	if (sigaction(SIGUSR2, &signal, NULL) == -1)
		ft_putstr_fd("ERROR USING SIGUSR2\n", 1);
	infinite_wait();
	return (0);
}

void	print_pid(void)
{
	ft_putstr_fd("Server start with pid: \033[0;32m", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\033[0m\n", 1);
}

void	client_signal_handler(int signal, siginfo_t *info, void *context)
{
	static int		pid = 0;
	static size_t	message = 0;
	static size_t	counter = 0;

	if (pid == 0)
	{
		ft_putstr_fd("\nMessage from \033[0;36m", 1);
		pid = info->si_pid;
		ft_putnbr_fd(pid, 1);
		ft_putstr_fd("\033[0m : ", 1);
	}
	if (signal == SIGUSR1)
		message = (message << 1) + 1;
	else if (signal == SIGUSR2)
		message = (message << 1);
	counter++;
	if (counter == 8)
	{
		handle_character(&message, &pid);
		counter = 0;
	}
}

void	handle_character(size_t *message, int *pid)
{
	char	c;

	c = (char)(*message);
	if (c == '\0')
	{
		kill(*pid, SIGUSR1);
		(*pid) = 0;
		ft_putchar_fd('\n', 1);
	}
	else
		ft_putchar_fd(c, 1);
	(*message) = 0;
}

void	infinite_wait(void)
{
	while (1)
		pause();
}
