/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_splitter.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/18 14:36:27 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/21 17:31:41 by wsonepou      ########   odam.nl         */
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
		return (c == ' ' || (c >= '\t' && c <= '\r'));
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	return (i);
}

/* Fix the ${HOME} brackets */
int	checking_var(t_shell *shell, char *str)
{
	int		i;
	t_env	*tmp;
	char	*var;

	i = 1;
	while (ft_isalnum(str[i]))
		i++;
	shell->input->word_len -= i;
	var = malloc(i * sizeof(char));
	if (var == NULL)
		kill_program(shell, "Failed mallocing var name", 6);
	ft_strlcpy(var, str + 1, i - 1);
	tmp = shell->env_list;
	while (tmp != NULL)
	{
		if (!ft_strncmp(var, tmp->var_name, i))
		{
			shell->input->var_val = tmp->var_val;
			shell->input->word_len += ft_strlen(tmp->var_val) - 2;
			break ;
		}
		tmp = tmp->next;
	}
	free(var);
	return (i);
}

static int	char_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		return (1);
	else if (str[i] == '$')
		while (str[i] != ' ' && str[i] != '\0')
			i++;
	else if (str[i] == '<' || str[i] == '>')
	{
		if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
			return (2);
		return (1);
	}
	return (0);
}

void	ft_copystr(char *dst, char *src, t_shell *shell)
{
	int	i;
	int	o;
	int	p;

	i = 0;
	o = 0;
	p = 1;
	while (o < shell->input->word_len)
	{
		if (src[i] == '\'')
		{
			i++;
			while (src[i] != '\'')
				dst[o++] = src[i++];
			i++;
		}
		else if (src[i] == '"')
		{
			i++;
			while (src[i] != '"')
			{
				if (src[i] == '$')
				{
					i += checking_var(shell, src + i);
					while (shell->input->var_val[p] != '"')
						dst[o++] = shell->input->var_val[p++];
					o++;
					p = 1;
					shell->input->var_val = NULL;
				}
				else
					dst[o++] = src[i++];
			}
			i++;
		}
		else if (src[i] == '$')
			{
				i += checking_var(shell, src + i);
				while (shell->input->var_val[p] != '"' && shell->input->var_val[p] != '\0')
					dst[o++] = shell->input->var_val[p++];
				o++;
				p = 1;
				shell->input->var_val = NULL;
			}
		else
			dst[o++] = src[i++];

	}
	dst[o] = '\0';
}

int	ft_wordlength(t_shell *shell, char *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	shell->input->word_len = 0;
	while (!ft_is_whitespace(str[i]) && str[i] != '\0' && char_check(str + i) == 0)
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			quotes += 2;
			i++;
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
			{
				if (str[i] == '$')
					i += checking_var(shell, str + i);
				else
					i++;
			}
			i++;
			quotes += 2;
		}
		else if (str[i] == '$')
			i += checking_var(shell, str + i);
		else
			i++;
	}
	shell->input->word_len += i - quotes;
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
	return (node);
}

void	get_files(t_shell *shell, t_ctable *cnode, char *cmdline)
{
	t_file	*new;
	int		i;

	i = 0;
	while (cmdline[i] != '\0' && cmdline[i] != '|')
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
		if (new != NULL && new->type == '<')
			lstadd_back(&cnode->infiles, new);
		else if (new != NULL && new->type == '>')
			lstadd_back(&cnode->outfiles, new);
		i += shell->input->word_len;
		if (shell->input->word_len == 0)
			i++;
		shell->input->word_len = 0;
	}
	shell->input->cmd_seg = i;
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
	get_files(shell, cnode, line);
	// get_cmd(shell, cnode, line);
	cnode->next = NULL;
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
