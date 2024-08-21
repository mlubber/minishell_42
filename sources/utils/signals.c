/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/09 11:12:52 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/21 20:10:23 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int signal)
{
	printf("signal %d\n", signal);
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(t_shell *shell, int i)
{
	struct sigaction	si;

	printf("init_signals\n");
	if (i == 1)
	{
		si.sa_handler = &sigint_handler;
		if (sigaction(SIGINT, &si, NULL) == -1)
			kill_program(shell, "setting SIGINT failed", errno);
	}
	else
	{
		si.sa_handler = SIG_DFL;
		if (sigaction(SIGINT, &si, NULL) == -1)
			kill_program(shell, "setting SIGINT to default failed", errno);
	}
}
