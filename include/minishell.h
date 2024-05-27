/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 06:12:53 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/05/27 13:38:49 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include "../libraries/libft/include/libft.h"
# include "../libraries/libft/include/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_tools
{
	char	*args;
	char	**paths;
	char	**envp;
	char	*pwd;
	char	*old_pwd;
}	t_tools;

void	ft_readline(char *line);
void	ft_free_2d_arr(char **arr);
char	**ft_copy_envp(char **envp);
int		ft_find_pwd(t_tools *tools);
char	*find_path(char **envp);
int		ft_parse_envp(t_tools *tools);
int		ft_reset_tools(t_tools *tools);
int		ft_minishell_loop(t_tools *tools);
int		ft_mini_env(t_tools *tools);
int		ft_mini_pwd(t_tools *tools);

#endif