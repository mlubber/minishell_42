/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/24 14:46:20 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/08/20 16:15:31 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cmd_arg_count(t_shell *shell, char *cmdline)
{
	int	count;

	count = 0;
	while (*cmdline && *cmdline != '|')
	{
		if (*cmdline == '<' || *cmdline == '>')
			cmdline += skip_file_or_word(cmdline, *cmdline, 0);
		else if (*cmdline == '$')
		{
			cmdline += get_wordlength(shell, cmdline);
			if (shell->input->word_len > 0)
				count++;
		}
		else
		{
			count++;
			cmdline += get_wordlength(shell, cmdline);
		}
		cmdline += check_whitespace(cmdline, 0);
	}
	return (count);
}

int	set_cmd(t_shell *shell, t_ctable *cnode, char *cmdline, int i)
{
	int	len;

	len = get_wordlength(shell, cmdline);
	cnode->cmd_array[i] = malloc((shell->input->word_len + 1) * sizeof(char));
	if (!cnode->cmd_array[i])
		kill_program(shell, "failed mallocing cmd node 2d array", errno);
	copy_word(cnode->cmd_array[i], cmdline, shell, 0);
	return (len);
}

void	parse_cmd(t_shell *shell, t_ctable *cnode, char *cmdline, int i)
{
	int	cmd_c;
	int	var_len;

	cmd_c = cmd_arg_count(shell, cmdline);
	if (cmd_c == 0)
		return ;
	cnode->cmd_array = malloc((cmd_c + 1) * sizeof(char *));
	if (!cnode->cmd_array)
		kill_program(shell, "cmd_array mallocing failed!", errno);
	cnode->cmd_array[cmd_c] = NULL;
	while (*cmdline && *cmdline != '|')
	{
		if (*cmdline == '<' || *cmdline == '>')
			cmdline += skip_file_or_word(cmdline, *cmdline, 0);
		else if (*cmdline == '$' && check_var(cmdline))
		{
			var_len = get_wordlength(shell, cmdline);
			if (shell->input->word_len > 0)
				set_cmd(shell, cnode, cmdline, i++);
			cmdline += var_len;
		}
		else if (!check_whitespace(NULL, *cmdline))
			cmdline += set_cmd(shell, cnode, cmdline, i++);
		cmdline += check_whitespace(cmdline, 0);
	}
}
