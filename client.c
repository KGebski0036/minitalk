/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:09:25 by kgebski           #+#    #+#             */
/*   Updated: 2024/01/06 13:53:14 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft/libft.h"

int	main(int argc, char const *argv[])
{
	int					pid;
	int					i;
	struct sigaction	signal;

	if (argc != 3)
	{
		ft_putstr_fd("Wrong numbers of arguments\n \
			Expected: [pid] [message]", 1);
		return (0);
	}
	signal.sa_handler = server_signal_handler;
	if (sigaction(SIGUSR1, &signal, NULL) == -1)
		ft_putstr_fd("ERROR USING SIGUSR1\n", 1);
	pid = pid_check(ft_atoi(argv[1]));
	i = 0;
	while (argv[2][i])
		char2binary(pid, argv[2][i++]);
	char2binary(pid, '\0');
	return (0);
}

int	pid_check(int pid)
{
	if (pid < 0 && pid > 99998)
	{
		ft_putstr_fd("Invalid pid (scope: <1; 99998>)", 1);
		exit(1);
	}
	else if (kill(pid, 0) != 0)
	{
		ft_putstr_fd("The server did not responde", 1);
		exit(1);
	}
	return (pid);
}

void	char2binary(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) % 2)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(200);
		i--;
	}
}

void	server_signal_handler(int signal)
{
	if (signal == SIGUSR1)
		ft_putstr_fd("\033[0;32mMessage delivered :D\033[0m\n", 1);
}
