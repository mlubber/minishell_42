/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/09 11:12:52 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/06 17:36:07 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int signal)
{
	(void)signal;
	g_signal = 1;
	// if (signal == SIGINT)
	// {
	// 	printf("Process %d received SIGINT\n", getpid());
	// 	rl_on_new_line();
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// }
}

void init_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

// void	sigint_handler(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		printf("Child process %d received SIGINT\n", getpid());
// 		exit(0);
// 	}
// }

// void	sigint_handler_parent(int signal, siginfo_t *info, void *ucontext)
// {
// 	(void)info;
// 	(void)ucontext;
// 	if (signal == SIGINT)
// 	{
// 		g_signal = 2;
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

// void init_signals(void)
// {
// 	struct sigaction	sa;

// 	sa.sa_handler = &sigint_handler_parent;
// 	sa.sa_flags = SA_SIGINFO;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// }

// void setup_signals(t_shell *shell)
// {
// 	t_ctable	*tmp;
// 	int			num;
	
// 	num = 0;
// 	shell->context->num_children = 0;
// 	tmp = shell->input->cnode;
// 	while (tmp != NULL)
// 	{
// 		num++;
// 		tmp = tmp->next;
// 	}
// 	shell->context->num_children = num;
// 	shell->context->children = malloc(num * sizeof(pid_t));
// 	if (shell->context->children == NULL)
// 		kill_program(shell, "Failed to allocate memory for children", errno);
// 	ft_memset(shell->context->children, 0, num * sizeof(pid_t));
// 	init_signals();
// }

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
