/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_files.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/17 14:16:26 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/19 16:42:51 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_file	*make_file_node(t_shell *shell, char *line, t_type type)
{
	t_file	*node;
	int			i;
	int			o;

	i = 1;
	node = malloc(sizeof(t_file));
	if (!node)
		kill_program(shell, "failed to malloc infile node!", 6);
	node->next = NULL;
	node->type = type;
	while (line[i] == '<' || line[i] == '>' || skip_whitespace(NULL, line[i]))
		i++;
	o = ft_wordlength(shell, line + i);
	node->str = malloc(o + 1);
	ft_copystr(node->str, line + i, shell);
	shell->input->word_len;
	return (node);
}

void	get_files(t_shell *shell, t_ctable **cnode, char *cmdline)
{
	t_file	*new;
	int		i;

	i = 0;
	while (cmdline[i] != '\0' && cmdline[i] != '|')
	{
		if (cmdline[i] == '<' && cmdline[i + 1] == '<')
			new = make_file_node(shell, cmdline + i, t_in_heredoc);
		else if (cmdline[i] == '<')
			new = infile_red_1(shell, cmdline + i);
		else if (cmdline[i] == '>' && cmdline[i + 1] == '>')
			new = outfile_red_2(shell, cmdline + i, 2);
		else if (cmdline[i] == '>')
			new = outfile_red_1(shell, cmdline + i, 1);
		if (new != NULL && new->type == '<')
			ft_lstadd_back(cnode, new);
		else if (new != NULL && new->type == '>')
			ft_lstadd_back(cnode, new);
		i += shell->input->word_len;
		if (shell->input->word_len != 0)
			i++;
		shell->input->word_len = 0;
		new = NULL;
	}
}
