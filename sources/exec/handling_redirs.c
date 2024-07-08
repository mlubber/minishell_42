/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handling_redirs.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 14:35:10 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/08 10:45:55 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// FOR DISCUSSION              <-------------------
// - If there are heredocs, but the heredoc is not the last infile, do we still run it?
// ---- In bash heredocs are ran before the opening of any other infile, no matter the order they are in, in the cmdline





// static void	ft_heredoc(t_file *infile) // needs lots of work
// {
// 	char	*str;
// 	int		limiter_len;

// 	limiter_len = 0;
// 	while (infile->str[limiter_len])
// 		limiter_len++;
// 	while (1)
// 	{
// 		str = get_next_line(0);
// 		if (str == NULL)
// 			break ;
// 		if (strncmp(str, infile->str, limiter_len) == 0
// 			&& str[limiter_len] == '\n')
// 		{
// 			free(str);
// 			break ;
// 		}
// 		write(cnode->fds[1], str, ft_strlen(str));
// 		free (str);
// 	}
// 	// if (dup2(info->fds[0], STDIN_FILENO) == -1)
// 	// 	kill_program(info, "child dup2 fds[0]", errno);
// 	// closing_fds(info->fds);
// }


static char	*open_outfiles(t_shell *shell, t_ctable *cnode, t_file *outfile)
{
	t_file	*tmp;

	tmp = cnode->outfiles;
	while (outfile != NULL)
	{
		if (cnode->outfile != 0)
			if (close(cnode->outfile) == -1)
				printf("Failed closing outfile fd %d\n", cnode->outfile);
		if (outfile->type == t_out_trunc)
			cnode->outfile = open(outfile->str, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		else
			cnode->outfile = open(outfile->str, O_CREAT | O_APPEND | O_WRONLY, 0777);
		if (cnode->outfile == -1)
			return (outfile->str);
		if (dup2(cnode->outfile, STDIN_FILENO) == -1)
			kill_program(shell, "Failed dup2 infile", errno);	
		outfile = outfile->next;
	}
	return (NULL);
}

// Few different cases to check for:
// -- No infiles & heredocs
// -- Infiles but no heredocs
// -- No infiles, but heredocs
// -- Both infiles and heredocs, but last is an infile
// -- Both infiles and heredocs, but last is a heredoc
static char	*open_infiles(t_shell *shell, t_ctable *cnode, t_file *infile)
{
	while (infile != NULL)
	{
		if (infile->type == t_in_file)
		{
			if (cnode->infile != 0)
				if (close(cnode->infile) == -1)
					printf("Failed closing infile fd %d\n", cnode->infile);
			cnode->infile = open(infile->str, O_RDONLY);
			if (cnode->infile == -1)
				return (infile->str);
			if (dup2(cnode->infile, STDIN_FILENO) == -1)
				kill_program(shell, "Failed dup2 infile", errno);	
		}
		infile = infile->next;
	}
	return (NULL);	
}


bool	handling_redirs(t_shell *shell, t_ctable *cnode)
{
	t_file	*infile;
	char	*file;

	infile = cnode->infiles;
	while (infile != NULL)
	{
		// if (infile->type == t_in_heredoc)
		// 	ft_heredoc(infile);
		infile = infile->next;
	}
	file = open_infiles(shell, cnode, cnode->infiles);
	if (file != NULL)
	{
		printf("Error: Couldn't open file: %s\n", file);
		return (false);
	}
	file = open_outfiles(shell, cnode, cnode->outfiles);
	if (file != NULL)
	{
		printf("Error: Couldn't open file: %s\n", file);
		return (false);
	}
	return (true);
}
