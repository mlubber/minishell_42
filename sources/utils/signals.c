/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/09 11:12:52 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/22 12:19:12 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_signal = signal;
}

void	init_signals(t_shell *shell, int i)
{
	struct sigaction	si;
	struct sigaction	sq;

	if (i == 1)
	{
		si.sa_handler = &sigint_handler;
		sq.sa_handler = SIG_IGN;
	}
	else if (i > 1)
	{
		si.sa_handler = SIG_DFL;
		if (i == 2)
			sq.sa_handler = SIG_DFL;
	}
	if (sigaction(SIGINT, &si, NULL) == -1)
		kill_program(shell, "setting SIGINT failed", errno);
	if (i != 3)
		if (sigaction(SIGQUIT, &sq, NULL) == -1)
			kill_program(shell, "setting SIGQUIT failed", errno);
}
