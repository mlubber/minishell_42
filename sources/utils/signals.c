/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/09 11:12:52 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/07/15 16:44:11 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		// printf("SIGINT received!\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_putchar_fd('\n', STDOUT_FILENO);
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
	}
}

void	sigquit_handler(int signal)
{
	if (signal == SIGQUIT)
	{
		// printf("SIGQUIT received!\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_putchar_fd('\n', STDOUT_FILENO);
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
	}
}

void	init_signals(void)
{
	struct sigaction	si;
	struct sigaction	sq;

	si.sa_handler = &sigint_handler;
	sq.sa_handler = &sigquit_handler;
	sigaction(SIGINT, &si, NULL);
	sigaction(SIGQUIT, &sq, NULL);
	// signal(SIGINT, sig_handler);
	// signal(SIGQUIT, sig_handler);
}
