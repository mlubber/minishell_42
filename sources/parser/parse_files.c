/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_files.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/24 14:37:50 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/09/05 11:05:45 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_file	*lstlast(t_file *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

static void	lstadd_back(t_ctable *cnode, t_file *new, char c)
{
	if (c == '<')
	{
		if (!cnode->infiles)
			cnode->infiles = new;
		else
			lstlast(cnode->infiles)->next = new;
	}
	else if (c == '>')
	{
		if (!cnode->outfiles)
			cnode->outfiles = new;
		else
			lstlast(cnode->outfiles)->next = new;
	}
}

static t_file	*make_file_node(t_shell *shell, char *line,
		t_type type, int i)
{
	t_file	*node;

	node = malloc(sizeof(t_file));
	if (!node)
		kill_program(shell, "failed to malloc infile node!", errno);
	node->next = NULL;
	node->type = type;
	while (line[i] == '<' || line[i] == '>' || check_whitespace(NULL, line[i]))
		i++;
	get_wordlength(shell, line + i);
	if (shell->input->word_len == 0
		|| (type == t_in_heredoc && check_var(line + i)))
	{
		get_wordlength(shell, line + i + 1);
		node->str = malloc(++shell->input->word_len + 1 * (sizeof(char)));
		node->str[0] = '$';
		copy_word(node->str, line + i + 1, shell, 1);
	}
	else
	{
		node->str = malloc(shell->input->word_len + 1 * (sizeof(char)));
		copy_word(node->str, line + i, shell, 0);
	}
	return (node);
}

void	parse_files(t_shell *shell, t_ctable *cnode, char *cmd)
{
	t_file	*new;
	int		i;

	i = 0;
	while (i < shell->input->cmd_seg)
	{
		new = NULL;
		if (cmd[i] == '\'' || cmd[i] == '"')
			i += skip_quotes(cmd + i, cmd[i]);
		if (cmd[i] == '<' && cmd[i + 1] == '<')
			new = make_file_node(shell, cmd + i, t_in_heredoc, 0);
		else if (cmd[i] == '<')
			new = make_file_node(shell, cmd + i, t_in_file, 0);
		else if (cmd[i] == '>' && cmd[i + 1] == '>')
			new = make_file_node(shell, cmd + i, t_out_append, 0);
		else if (cmd[i] == '>')
			new = make_file_node(shell, cmd + i, t_out_trunc, 0);
		if (new != NULL && (cmd[i] == '<' || cmd[i] == '>'))
			lstadd_back(cnode, new, cmd[i]);
		if (new != NULL)
			i += skip_file_or_word(cmd + i, cmd[i], 0);
		if (cmd[i] != '"' && cmd[i] != '\'' && shell->input->word_len == 0)
			i++;
		shell->input->word_len = 0;
	}
}
