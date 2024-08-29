/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 11:27:19 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/08/29 14:59:58 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	ft_checkfordigits(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (false);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
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
	if (double_dash == false
		|| (double_dash == true && cmds[2] != NULL && is_num == false))
	{
		ft_putstr_fd(cmds[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
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
		ft_putstr_fd(cmds[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		kill_program(shell, NULL, 2);
	}
	if (cmds[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		shell->exit_code = 1;
		return ;
	}
	else
		kill_program(shell, NULL, ft_atoll(cmds[1]));
}

void	ft_mini_exit(t_shell *shell, char **cmds)
{
	if (cmds[1] != NULL)
	{
		if (ft_isdigit(cmds[1][0]) > 0
			|| (cmds[1][0] == '-' && ft_isdigit(cmds[1][1]))
			|| (cmds[1][0] == '+' && ft_isdigit(cmds[1][1])))
			digit_started(shell, cmds);
		else if (cmds[1][0] == '-')
			dash_started(shell, cmds);
		else
		{
			ft_putstr_fd(cmds[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			kill_program(shell, NULL, 2);
		}
	}
	else if (shell->input->cnode->next)
		kill_program(shell, NULL, 0);
	else
		kill_program(shell, "exit\n", 0);
}
