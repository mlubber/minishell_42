/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 06:12:53 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/07/09 09:49:44 by mlubbers      ########   odam.nl         */
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
# include <errno.h>
# include "../libraries/libft/include/libft.h"
# include "../libraries/libft/include/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef enum { 		// Dit zijn, denk ik, de verschillende cmd types die we moeten bijhouden
	t_cmd,			// Dit is gewoon de cmd + flags of arguments, bijv. 'ls -la'
	t_pipe,			// '|'
	t_in_file,		// '<'
	t_in_heredoc,	// '<<'
	t_out_trunc,	// '>'
	t_out_append,	// '>>' 
}	t_type;

typedef struct s_copy
{
	int		src;
	int		dest;
	char	quote;
}	t_copy;

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
	char			**cmd_array;	// Double array voor de cmd + flags of arguments
	t_file			*infiles;
	t_file			*outfiles;
	int				infile;
	int				outfile;
	bool			run_cmd;
	struct s_ctable	*next;
}	t_ctable;

/* Input struct */
typedef struct s_input
{
	char		*line; // Input str from user
	t_ctable	*cnode; // head of the cmds linked list
	char		*var_val; // pointer to the value of the found env variable
	int			var_len; // length of the variable name
	int			var_val_len; // length of the variable value
	int			word_len; // length of the word, excluding var_len & quotes, including var_val_len
	int			cmd_seg; // Length of the segment until a pipe or \0, including infiles, outfiles, command and arguments
	int			cmds_count; // Amount of cmds
	int			fds[2]; // pipe filedescriptor array 	<<-------- Kan misschien beter in ctable struct
}	t_input;

typedef struct s_shell
{
	char		**envp;
	char		**paths;
	char		*pwd;
	char		*old_pwd;
	int			env_size;
	int			exit_code;
	int			stdinput;
	int			stdoutput;
	t_env		*env_list;
	t_input		*input;
}	t_shell;

// Main


// Environment
t_env	*create_env_node(t_shell *shell, char *str);
void	building_env(t_shell *shell, t_env **env_list, char **envp);
char	*set_var_value(char *str);


// Parser
int		input_checker(char **input);
void	create_ctable(t_shell *shell, char *cmdline);
int		get_wordlength(t_shell *shell, char *str);
void	copy_word(char *dst, char *src, t_shell *shell);
void	parse_files(t_shell *shell, t_ctable *cnode, char *cmdline);
void	parse_cmd(t_shell *shell, t_ctable *cnode, char *cmdline);

int		char_check(char *str);
int		skip_quotes(char *cmdline, char quote);
int		skip_file_or_word(char *cmdline, char c, int i);
int		check_whitespace(char *str, char c);


// Bash shell
void	ft_minishell_loop(t_shell *shell);


// Executor
void	start_execution(t_shell *shell);
bool	handling_redirs(t_shell *shell, t_ctable *cnode);


// Builtins
int		ft_mini_echo(t_shell *shell, char **cmds);
int		ft_mini_cd(t_shell *shell, char **cmds);
int		ft_mini_pwd(t_shell *shell, char **cmds);
int		ft_mini_export(t_shell *shell, char **cmds);
int		ft_mini_unset(t_shell *shell, char **cmds);
int		ft_mini_env(t_shell *shell, char **cmds);
int		ft_mini_exit(t_shell *shell, char **cmds);

void	ft_free_arr(char ***arr);
int		check_alpha_num(char *str);
char	*path_check(t_shell *shell, char *path);
void	ft_check_upper_dir(t_shell *shell);


// Kill program
void	kill_program(t_shell *shell, char *msg, int i);
void	free_env_node(t_env **node);

void	free_cmd_list(t_ctable **head);


#endif