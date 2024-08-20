/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 11:27:19 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/08/19 14:39:38 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool		ft_checkfordigits(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (false);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' && str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static unsigned int	ft_atoll(char *num_str)
{
	long long	i;
	long long	min;
	long long	o;

	min = 1;
	o = 0;
	i = check_whitespace(num_str, 0);
	if (num_str[i] == '-' || num_str[i] == '+')
	{
		if (num_str[i] == '-')
			min = -1;
		i++;
	}
	while (num_str[i] >= '0' && num_str[i] <= '9')
	{
		o = o * 10 + (num_str[i] - '0');
		i++;
	}
	o *= min;
	o = (unsigned int)o;
	o %= 256;
	return (o);
}

static void	dash_started(t_shell *shell, char **cmds)
{
	bool	double_dash;
	bool	is_num;

	double_dash = false;
	if (cmds[1][0] == '-' && cmds[1][1] == '-' && cmds[1][2] == '\0')
		double_dash = true;
	is_num = ft_checkfordigits(cmds[2]);
	if (double_dash == false || (double_dash == true && cmds[2] != NULL && is_num == false))
	{
		if (dup2(shell->stdoutput, STDOUT_FILENO) == -1)
			kill_program(shell, "Dup2 failed in mini exit", errno);
		printf("%s: numeric value required\n", cmds[1]);
		kill_program(shell, NULL, 2);
	}
	else if (is_num == true)
		kill_program(shell, NULL, ft_atoll(cmds[2]));
	kill_program(shell, NULL, 0);
}

static void	digit_started(t_shell *shell, char **cmds)
{
	if (ft_checkfordigits(cmds[1]) == false)
	{
		if (dup2(shell->stdoutput, STDOUT_FILENO) == -1)
			kill_program(shell, "Dup2 failed in mini exit", errno);
		printf("%s: numeric value required\n", cmds[1]);
		kill_program(shell, NULL, 2);
	}
	if (cmds[2] != NULL)
	{
		if (dup2(shell->stdoutput, STDOUT_FILENO) == -1)
			kill_program(shell, "Dup2 failed in mini exit", errno);
		printf("exit: too many arguments\n");
		return ;	
	}
	else
		kill_program(shell, NULL, ft_atoll(cmds[1]));
}

int	ft_mini_exit(t_shell *shell, char **cmds)
{
	if (cmds[1] != NULL)
	{
		if (ft_isdigit(cmds[1][0]) > 0 || (cmds[1][0] == '-' && ft_isdigit(cmds[1][1])) || (cmds[1][0] == '+' && ft_isdigit(cmds[1][1])))
			digit_started(shell, cmds);
		else if (cmds[1][0] == '-')
			dash_started(shell, cmds);
		else
		{
			if (dup2(shell->stdoutput, STDOUT_FILENO) == -1)
				kill_program(shell, "Dup2 failed in mini exit", errno);
			printf("%s: numeric value required\n", cmds[1]);
			kill_program(shell, NULL, 2);
		}
	}
	else if (shell->input->cnode->next)
		kill_program(shell, NULL, 0);
	else
		kill_program(shell, "exit\n", 0);
	return (1);
}
