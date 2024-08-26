/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/09 11:12:52 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/26 11:25:11 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int signal)
{
	// printf("\nglobal handler: %d\n", g_signal);
	if (g_signal == -1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (signal == SIGINT && g_signal != -1)
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

	ft_memset(&si, 0, sizeof(si));
	ft_memset(&sq, 0, sizeof(sq));
	si.sa_flags = SA_RESTART;
	sigemptyset(&si.sa_mask);
	if (i == 1)
	{
		si.sa_handler = &sigint_handler;
		sq.sa_handler = SIG_IGN;
	}
	if (i > 1)
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

// void	init_signals(t_shell *shell, int i)
// {
// 	if (i == 1)
// 	{
// 		if (signal(SIGINT, &sigint_handler) == SIG_ERR)
// 			kill_program(shell, "setting SIGINT failed", errno);
// 		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
// 			kill_program(shell, "setting SIGQUIT failed", errno);
// 	}
// 	if (i != 1)
// 		if (signal(SIGINT, SIG_DFL) == SIG_ERR)
// 			kill_program(shell, "setting SIGINT failed", errno);
// 	if (i == 2)
// 		if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
// 			kill_program(shell, "setting SIGQUIT failed", errno);
// }
