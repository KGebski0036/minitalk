/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:10:18 by kgebski           #+#    #+#             */
/*   Updated: 2023/06/04 17:52:23 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

//       --=[ server.c ]=--       //
void	print_pid(void);
void	client_signal_handler(int signal, siginfo_t *info, void *context);
void	infinite_wait(void);
void	handle_character(size_t *message, int *pid);

//       --=[ client.c ]=--       //
int		pid_check(int pid);
void	server_signal_handler(int signal);
void	char2binary(int pid, char c);

#endif