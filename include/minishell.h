/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 06:12:53 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/02 13:04:22 by wsonepou      ########   odam.nl         */
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

typedef struct s_lexer
{
	char			*str;
	int				node_nbr;
	struct s_lexer	*prev;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_tools
{
	char	*full_string;
	char	**paths;
	char	**envp;
	char	*pwd;
	char	*old_pwd;
	t_lexer	*lexer_list;
}	t_tools;

void	ft_readline(char *line);
void	ft_free_2d_arr(char **arr);
char	**ft_copy_envp(char **envp);
int		ft_find_pwd(t_tools *tools);
char	*find_path(char **envp);
int		ft_parse_envp(t_tools *tools);
int		ft_init_tools(t_tools *tools);
int		ft_reset_tools(t_tools *tools);
int		ft_minishell_loop(t_tools *tools);
int		ft_mini_env(t_tools *tools);
int		ft_mini_pwd(t_tools *tools);
int		ft_is_whitespace(char c);
int		ft_skip_spaces(int i, char *str);
int		ft_add_node(char *str, t_lexer **lexer_list);
int		ft_read_word(int i, char *str, t_lexer **lexer_list);
int		ft_reader(t_tools *tools);
t_lexer	*ft_new_lexer_node(char *str);
void	ft_lexer_add_back(t_lexer **lexer_list, t_lexer *new);
int		ft_handle_quotes(int i, char *str, char c);

void	kill_program(t_tools *tools, char *msg, int i); // toegevoegd

#endif