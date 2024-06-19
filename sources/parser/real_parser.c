/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   real_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/18 14:36:27 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/19 17:33:02 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_file	*lstlast(t_file *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_file **lst, t_file *new)
{
	if (!*lst)
		*lst = new;
	else
		lstlast(*lst)->next = new;
}

int	skip_whitespace(char *str, char c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'));
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	return (i);
}

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
	// shell->input->word_len;
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
			new = make_file_node(shell, cmdline + i, t_in_file);
		else if (cmdline[i] == '>' && cmdline[i + 1] == '>')
			new = make_file_node(shell, cmdline + i, t_out_append);
		else if (cmdline[i] == '>')
			new = make_file_node(shell, cmdline + i, t_out_trunc);
		if (new != NULL && new->type == '<')
			lstadd_back(&cnode->infile, new);
		else if (new != NULL && new->type == '>')
			lstadd_back(cnode->infile, new);
		i += shell->input->word_len;
		if (shell->input->word_len != 0)
			i++;
		shell->input->word_len = 0;
		new = NULL;
	}
}

t_ctable	*create_ctable_node(t_shell *shell, char *line)
{
	t_ctable	*cnode;

	cnode = malloc(sizeof(t_ctable));
	if (cnode == NULL)
		kill_program(shell, "couldn't malloc ctable node!", 6);
	cnode->infiles = NULL;
	cnode->outfiles = NULL;
	cnode->cmds = NULL;
	get_files(shell, &cnode, line);
	// get_cmd(shell, line, cnode);
	cnode->next = NULL;
	while (line[shell->input->cmd_seg] != '\0' && line[shell->input->cmd_seg] != '|')
		shell->input->cmd_seg++;
	return (cnode);
}


void	create_ctable(t_shell *shell, char *line)
{
	t_ctable	*tmp;
	t_ctable	*new;

	line += skip_whitespace(line, 0);
	shell->input->cmds = create_ctable_node(shell, line);
	line += shell->input->cmd_seg;
	tmp = shell->input->cmds;
	while (*line)
	{
		line += skip_whitespace(line, 0);
		if (*line == '\0')
			break ;
		new = create_ctable_node(shell, line);
		tmp->next = new;
		tmp = tmp->next;
		line += shell->input->cmd_seg;
		shell->input->cmd_seg = 0;
	}
}


// VOOR TESTING VANAF HIER
static void	init_shell(t_shell *shell)
{
	shell->paths = NULL;
	shell->envp = NULL;
	shell->pwd = NULL;
	shell->old_pwd = NULL;
	shell->env_size = 0;
	shell->env_list = NULL;
	shell->input->cmds = NULL;
	shell->input->var_val = NULL;
	shell->input->var_val_len = 0;
	shell->input->var_len = 0;
	shell->input->word_len = 0;
	shell->input->cmd_seg = 0;
}

int	main()
{
	t_shell	shell;
	t_input	input;
	char str[] = "<this <is >>a <<redirect";

	init_shell(&shell);
	create_ctable(&shell, str);
	printf("%s\n", shell.input->cmds->infiles->str);

	return (0);
}