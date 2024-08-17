/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finish_line.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/16 15:53:57 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/08/16 11:05:57 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pipejoin(t_shell *shell, char *cmdline, char **addition)
{
	int		i;
	int		o;
	char	*p;
	char	*tmp;

	i = 0;
	tmp = *addition;
	o = ft_strlen(cmdline) + ft_strlen(tmp);
	p = malloc((o + 1) * sizeof(char));
	if (!p)
		kill_program(shell, "Failed mallocing pipejoin", errno);
	while (*cmdline)
		p[i++] = *cmdline++;
	while (*tmp)
		p[i++] = *tmp++;
	p[i] = '\0';
	free (shell->input->line);
	free (*addition);
	shell->input->line = p;
}

int	finish_line(t_shell *shell)
{
	char	*addition;
	int		i;
	int		x;

	i = 0;
	while (1)
	{
		addition = readline("pipe> ");
		if (addition == NULL)
			kill_program(shell, "readline in finish_line func failed", errno);
		i += check_whitespace(addition, 0);
		if (addition[i] == '\0')
		{
			free (addition);
			i = 0;
			continue ;
		}
		ft_pipejoin(shell, shell->input->line, &addition);
		x = input_checker(shell, shell->input->line);
		if (x == 0)
			return (0);
		else if (x == 2)
			return (2);
	}
}
