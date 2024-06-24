/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 06:12:53 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/24 16:08:43 by wsonepou      ########   odam.nl         */
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
	t_in_file,		// '<'
	t_in_heredoc,	// '<<'
	t_out_trunc,	// '>'
	t_out_append,	// '>>' 
}	t_type;

typedef struct s_env
{
	char			*str;
	char			*var_name;
	char			*var_val;
	bool			printed;
	int				node_num;
	struct s_env	*next;
}	t_env;

typedef struct s_file
{
	t_type			type;
	char			*str;
	struct s_file	*next;
}	t_file;

/* Command table linked list node */
typedef struct s_ctable		// ctable = command table
{
	char			**cmds;	// Double array voor de cmd + flags of arguments
	t_file			*infiles;
	t_file			*outfiles;
	int				infile;
	int				outfile;
	struct s_ctable	*next;
}	t_ctable;

/* Input struct */
typedef struct s_input
{
	char		*line;
	t_ctable	*cmds; // head of the cmds linked list
	char		*var_val; // pointer to the value of the found env variable
	int			var_len; // length of the variable name
	int			var_val_len; // length of the variable value
	int			word_len; // length of the word, excluding var_len & quotes, including var_val_len
	int			cmd_seg; // Length of the segment until a pipe or \0, including infiles, outfiles, command and arguments
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


// Utils
int		ft_is_whitespace(char c);
int		check_whitespace(char *str, char c); // Gaat ft_is_whitespace vervangen??
int		ft_handle_quotes(int i, char *str, char c);



// Parser
int		input_checker(char **input);
void	create_ctable(t_shell *shell, char *cmdline);
int		ft_wordlength(t_shell *shell, char *str);
void	ft_copystr(char *dst, char *src, t_shell *shell);
void	get_files(t_shell *shell, t_ctable *cnode, char *cmdline);
void	get_cmd(t_shell *shell, t_ctable *cnode, char *cmdline);

int	char_check(char *str);


// Bash shell
void	ft_minishell_loop(t_shell *shell);



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