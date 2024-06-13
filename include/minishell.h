/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 06:12:53 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/13 17:21:34 by wsonepou      ########   odam.nl         */
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

typedef enum { 		// Dit zijn, denk ik, de verschillende cmd types die we moeten bijhouden
	t_cmd,			// Dit is gewoon de cmd + flags of arguments, bijv. 'ls -la'
	t_pipe,			// '|'
	t_less,			// '<'
	t_d_less,		// '<<'
	t_greater,		// '>'
	t_d_greater,	// '>>' 
}	t_type;

// typedef struct s_ctable // command table linked list
// {
// 	char			*str;
// 	int				node_nbr;
// 	struct s_ctable	*prev;
// 	struct s_ctable	*next;
// }	t_ctable;

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

/* Command table linked list node */
typedef struct s_ctable {	// ctable = command table
	t_type			type;	// Dit is het type zoals hierboven
	char			**cmds;	// Double array voor de cmd + flags of arguments
	char			*file;	// Filenaam als er een redirect gevonden is
	struct s_ctable	*next;
}	t_ctable;

/* Input struct */
typedef struct s_input
{
	t_ctable	*cmds; // head of the cmds linked list
	char		*var_val; // pointer to the value of the found env variable
	int			var_len; // length of the variable name
	int			var_val_len; // length of the variable value
	int			cmd_len; // length of the word, excluding var_len & quotes, including var_val_len
	int			part_len; // length of input part that is used to get through the input string
}	t_input;

typedef struct s_shell
{
	char		**envp;
	char		**paths;
	char		*pwd;
	char		*old_pwd;
	int			env_size;
	t_env		*env_list;
	t_input		*input;
}	t_shell;

// Main


// Environment
t_env	*create_env_node(t_shell *shell, char *str);
void	building_env(t_shell *shell, t_env **env_list, char **envp);


// Lexer
int			ft_is_whitespace(char c);
int			ft_skip_spaces(int i, char *str);
int			ft_add_node(char *str, t_ctable **lexer_list);
int			ft_read_word(int i, char *str, t_ctable **lexer_list);
int			ft_reader(t_shell *shell);
t_ctable	*ft_new_lexer_node(char *str);
void		ft_lexer_add_back(t_ctable **lexer_list, t_ctable *new);
int			ft_handle_quotes(int i, char *str, char c);



// Parser
int		input_checker(char **input);
void	create_ctable(t_shell *shell, char *cmdline);



// Bash shell
void	ft_minishell_loop(t_shell *shell);
// int		ft_init_shell(t_shell *shell);
// int		ft_reset_shell(t_shell *shell);


// Builtins
int		ft_mini_echo(t_shell *shell, char **cmds);
int		ft_mini_cd(t_shell *shell, char **cmds);
int		ft_mini_pwd(t_shell *shell, char **cmds);
int		ft_mini_export(t_shell *shell, char **cmds);
int		ft_mini_unset(t_shell *shell, char **cmds);
int		ft_mini_env(t_shell *shell, char **cmds);
int		ft_mini_exit(t_shell *shell, char **cmds);



// Kill program
void	kill_program(t_shell *shell, char *msg, int i);
void	add_node_middle(t_shell *shell, t_env **head, int position, char *str);
void	free_env_node(t_env **node);
void	*ft_free_2d_arr(char ***arr, int i);


#endif