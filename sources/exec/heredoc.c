/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/13 13:52:28 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/08/29 17:26:18 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*add_newline(t_shell *shell, char *input)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc((ft_strlen(input) + 2) * sizeof(char));
	if (new == NULL)
		kill_program(shell, "Failed mallocing add_newline", errno);
	while (input[i])
	{
		new[i] = input[i];
		i++;
	}
	new[i++] = '\n';
	new[i] = '\0';
	return (new);
}

static void	close_heredoc_pipes(t_ctable *cnode)
{
	if (cnode->hd_pipe[0] != -1 && close(cnode->hd_pipe[0]) == -1)
		perror("cnode->hd_pipe[0]");
	if (cnode->hd_pipe[1] != -1 && close(cnode->hd_pipe[1]) == -1)
		perror("cnode->hd_pipe[1]");
	cnode->hd_pipe[0] = -1;
	cnode->hd_pipe[1] = -1;
}

static void	run_heredoc(t_shell *shell, t_ctable *cnode, t_file *infiles)
{
	char	*input;
	int		limiter_len;

	rl_clear_history();
	limiter_len = ft_strlen(infiles->str);
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			write_heredoc_error(infiles->str);
			break ;
		}
		if (ft_strncmp(input, infiles->str, limiter_len) == 0
			&& input[limiter_len] == '\0')
		{
			free(input);
			break ;
		}
		input = add_newline(shell, input);
		write(cnode->hd_pipe[1], input, ft_strlen(input));
		free(input);
	}
	shell->pid = 1;
	close_heredoc_pipes(cnode);
}

static pid_t	set_heredoc(t_shell *shell, t_ctable *cnode, t_file *infiles)
{
	pid_t	hd_pid;

	close_heredoc_pipes(cnode);
	if (pipe(cnode->hd_pipe) == -1)
		kill_program(shell, "Failed creating pipe", errno);
	g_signal = -1;
	hd_pid = fork();
	if (hd_pid == -1)
		kill_program(shell, NULL, errno);
	if (hd_pid == 0)
	{
		init_signals(shell, 3);
		run_heredoc(shell, cnode, infiles);
		kill_program(shell, NULL, 0);
	}
	if (close(cnode->hd_pipe[1]) == -1)
		perror("cnode->hd_pipe[1]");
	cnode->hd_pipe[1] = -1;
	return (hd_pid);
}

int	check_heredoc(t_shell *shell)
{
	t_ctable	*cnode;
	t_file		*infiles;
	pid_t		pid;
	int			status;

	cnode = shell->input->cnode;
	while (cnode != NULL)
	{
		infiles = cnode->infiles;
		while (infiles != NULL)
		{
			if (infiles->type == t_in_heredoc)
			{
				pid = set_heredoc(shell, cnode, infiles);
				waitpid(pid, &status, 0);
				if (WIFSIGNALED(status))
					return (130);
				else
					shell->exit_code = 0;
			}
			infiles = infiles->next;
		}
		cnode = cnode->next;
	}
	return (0);
}
