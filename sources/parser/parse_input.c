/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/18 14:36:27 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/08/06 16:27:59 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_whitespace(char *str, char c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (c == ' ' || (c >= '\t' && c <= '\r'));
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	return (i);
}

void	get_cmd_seg_len(t_shell *shell, char *cmdline)
{
	int	i;

	i = 0;
	while (cmdline[i] != '\0' && cmdline[i] != '|')
	{
		if (cmdline[i] == '\'')
		{
			i++;
			while (cmdline[i] != '\'')
				i++;
		}
		else if (cmdline[i] == '"')
		{
			i++;
			while (cmdline[i] != '"')
				i++;
		}
		i++;
	}
	shell->input->cmd_seg = i;
}

t_ctable	*create_ctable_node(t_shell *shell, char *line)
{
	t_ctable	*cnode;

	get_cmd_seg_len(shell, line);
	cnode = malloc(sizeof(t_ctable));
	if (cnode == NULL)
		kill_program(shell, "couldn't malloc ctable node!", 6);
	cnode->infiles = NULL;
	cnode->outfiles = NULL;
	cnode->infile = 0;
	cnode->outfile = 0;
	cnode->hd_pipe[0] = 0;
	cnode->hd_pipe[1] = 0;
	cnode->cmd_array = NULL;
	cnode->run_cmd = false;
	parse_files(shell, cnode, line);
	parse_cmd(shell, cnode, line);
	cnode->next = NULL;
	shell->input->node_count++;
	if (cnode->cmd_array != NULL)
		cnode->run_cmd = true;
	return (cnode);
}

void	create_ctable(t_shell *shell, char *line)
{
	t_ctable	*tmp;
	t_ctable	*new;

	line += check_whitespace(line, 0);
	shell->input->cnode = create_ctable_node(shell, line);
	line += shell->input->cmd_seg;
	tmp = shell->input->cnode;
	while (*line)
	{
		if (*line == '|')
			line++;
		line += check_whitespace(line, 0);
		if (*line == '\0')
			break ;
		new = create_ctable_node(shell, line);
		tmp->next = new;
		tmp = tmp->next;
		line += shell->input->cmd_seg;
		shell->input->cmd_seg = 0;
	}
}
