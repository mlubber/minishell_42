/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_files.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/24 14:37:50 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/26 16:55:49 by wsonepou      ########   odam.nl         */
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

static void	lstadd_back(t_file **lst, t_file *new)
{
	if (!*lst)
		*lst = new;
	else
		lstlast(*lst)->next = new;
}

static t_file	*make_file_node(t_shell *shell, char *line, t_type type)
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
	while (line[i] == '<' || line[i] == '>' || check_whitespace(NULL, line[i]))
		i++;
	o = get_wordlength(shell, line + i);
	node->str = malloc(o + 1);
	copy_word(node->str, line + i, shell);
	return (node);
}

void	parse_files(t_shell *shell, t_ctable *cnode, char *cmdline)
{
	t_file	*new;
	int		i;

	i = 0;
	while (i < shell->input->cmd_seg)
	{
		new = NULL;
		if (cmdline[i] == '<' && cmdline[i + 1] == '<')
			new = make_file_node(shell, cmdline + i, t_in_heredoc);
		else if (cmdline[i] == '<')
			new = make_file_node(shell, cmdline + i, t_in_file);
		else if (cmdline[i] == '>' && cmdline[i + 1] == '>')
			new = make_file_node(shell, cmdline + i, t_out_append);
		else if (cmdline[i] == '>')
			new = make_file_node(shell, cmdline + i, t_out_trunc);
		if (new != NULL && cmdline[i] == '<')
			lstadd_back(&cnode->infiles, new);
		else if (new != NULL && cmdline[i] == '>')
			lstadd_back(&cnode->outfiles, new);
		i += shell->input->word_len;
		if (shell->input->word_len == 0)
			i++;
		shell->input->word_len = 0;
	}
}
