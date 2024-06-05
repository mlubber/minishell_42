/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 06:12:53 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/04 16:35:22 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <stdbool.h>
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

typedef struct s_env
{
	char			*str;
	char			*var_name;
	char			*var_val;
	bool			printed;
	int				node_num;
	struct s_env	*next;
}	t_env;


typedef struct s_token
{
	char	*pipe;
	char	*bi_env;
	char	*bi_cd;
	char	*bi_exit;
	char	*bi_export;
	char	*bi_pwd;
}	t_token;


typedef struct s_shell
{
	char	*input;
	char	**paths;
	char	**envp;
	char	*pwd;
	char	*old_pwd;
	int		env_size;
	t_env	*env_list;
	t_lexer	*lexer_list;
}	t_shell;

// Main


// Environment
t_env	*create_env_node(t_shell *shell, char *str);
void	building_env(t_shell *shell, t_env **env_list, char **envp);


// Lexer
int		ft_is_whitespace(char c);
int		ft_skip_spaces(int i, char *str);
int		ft_add_node(char *str, t_lexer **lexer_list);
int		ft_read_word(int i, char *str, t_lexer **lexer_list);
int		ft_reader(t_shell *shell);
t_lexer	*ft_new_lexer_node(char *str);
void	ft_lexer_add_back(t_lexer **lexer_list, t_lexer *new);
int		ft_handle_quotes(int i, char *str, char c);


// Bash shell
void	ft_minishell_loop(t_shell *shell);
// int		ft_init_shell(t_shell *shell);
// int		ft_reset_shell(t_shell *shell);


// Builtins
int		ft_mini_env(t_shell *shell);
void	ft_mini_pwd(t_shell *shell);
int		ft_mini_export(t_shell *shell);
int		ft_mini_cd(t_shell *shell);



// Kill program
void	kill_program(t_shell *shell, char *msg, int i);
void	add_node_middle(t_shell *shell, t_env **head, int position, char *str);
void	free_env_node(t_env **node);
void	ft_free_2d_arr(char **arr);


#endif