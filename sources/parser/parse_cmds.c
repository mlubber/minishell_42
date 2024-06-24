/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmds.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/24 14:46:20 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/24 16:23:55 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	skip_file_or_word(char *cmdline, char c)
{
	int	i;

	if (c == '<' || c == '>')
	{
		i = 1;
		if (cmdline[i] == c)
			i = 2;
		i += check_whitespace(cmdline + i, 0);
		while (cmdline[i] && !check_whitespace(NULL, cmdline[i]) && !char_check(cmdline + i))
			i++;
		return (i);		
	}
	else
	{
		i = 0;
		while (cmdline[i] && !check_whitespace(NULL, cmdline[i]) && !char_check(cmdline + i))
			i++;
		return (i);
	}
}

int	cmd_arg_count(char *cmdline)
{
	int	count;

	count = 0;
	while (*cmdline && *cmdline != '|')
	{
		if (*cmdline == '<' || *cmdline == '>')
			cmdline += skip_file_or_word(cmdline, *cmdline);
		else if (ft_isalnum(*cmdline))
		{
			count++;
			while (*cmdline && !check_whitespace(NULL, *cmdline) && !char_check(cmdline))
				cmdline++;
		}
		cmdline += check_whitespace(cmdline, 0);
	}
	printf("Count: %d\n", count);
	return (count);
}


int	set_cmd(t_shell *shell, t_ctable *cnode, char *cmdline, int i)
{
	int	len;

	len = ft_wordlength(shell, cmdline);
	cnode->cmds[i] = malloc((shell->input->word_len + 1) * sizeof(char));
	if (!cnode->cmds[i])
		kill_program(shell, "failed mallocing cmd node 2d array", 6);
	ft_copystr(cnode->cmds[i], cmdline, shell);
	return (len);
}

void	get_cmd(t_shell *shell, t_ctable *cnode, char *cmdline)
{
	int	i;
	int	cmd_c;

	i = 0;
	cmd_c = cmd_arg_count(cmdline);
	if (cmd_c == 0)
		return ;
	cnode->cmds = malloc((cmd_c + 1) * sizeof(char *));
	if (!cnode->cmds)
		kill_program(shell, "cmd_array mallocing failed!", 6);
	cnode->cmds[cmd_c] = NULL;
	while (*cmdline && *cmdline != '|')
	{
		if (*cmdline == '<' || *cmdline == '>')
			cmdline += skip_file_or_word(cmdline, *cmdline);
		else if (!check_whitespace(NULL, *cmdline))
			cmdline += set_cmd(shell, cnode, cmdline, i++);
		cmdline += check_whitespace(cmdline, 0);
	}
}
