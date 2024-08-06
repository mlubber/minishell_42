/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/09 11:12:52 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/05 17:07:06 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
		exit(0);
}

void	sigint_handler_parent(int signal, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void init_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &sigint_handler_parent;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

// void	sigint_handler(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		// printf("SIGINT received!\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 		rl_redisplay();
// 		// ft_putstr_fd("minishell01: ", STDOUT_FILENO);
// 	}
// }

// void	sigquit_handler(int signal)
// {
// 	if (signal == SIGQUIT)
// 	{
// 		// printf("SIGQUIT received!\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 		ft_putstr_fd("minishell02: ", STDOUT_FILENO);
// 	}
// }

// void	init_signals(void)
// {
// 	struct sigaction	si;
// 	struct sigaction	sq;

// 	si.sa_handler = &sigint_handler;
// 	sq.sa_handler = &sigquit_handler;
// 	sigaction(SIGINT, &si, NULL);
// 	sigaction(SIGQUIT, &sq, NULL);
// 	// signal(SIGINT, sig_handler);
// 	// signal(SIGQUIT, sig_handler);
// }
