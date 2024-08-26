/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 06:12:53 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/26 15:49:04 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include <dirent.h>
# include "../libraries/libft/include/libft.h"
# include "../libraries/libft/include/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>

extern int	g_signal;

typedef enum s_type
{
	t_cmd,
	t_pipe,
	t_in_file,
	t_in_heredoc,
	t_out_trunc,
	t_out_append,
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
typedef struct s_ctable
{
	char			**cmd_array;
	t_file			*infiles;
	t_file			*outfiles;
	int				infile;
	int				outfile;
	int				hd_pipe[2];
	struct s_ctable	*next;
}	t_ctable;

/* Input struct 
	*line; Input str from user
	*cnode; head of the cmds linked list
	*var_val; pointer to the value of the found env variable
	var_len; length of the variable name
	var_val_len; length of the variable value
	word_len; length of the word, excl var_len & quotes, incl var_val_len
	cmd_seg; Length of the segment until a pipe or \0,
	node_count; Amount of cmds
	fds[2]; Filedescriptor array in case pipes are used
	*/
typedef struct s_input
{
	char		*line;
	t_ctable	*cnode;
	char		*var_val;
	int			var_len;
	int			var_val_len;
	int			word_len;
	int			cmd_seg;
	int			node_count;
	int			fds[2];
}	t_input;

typedef struct s_shell
{
	char		*pwd;
	char		*old_pwd;
	char		*home;
	int			env_size;
	int			exit_code;
	int			stdinput;
	int			stdoutput;
	pid_t		pid;
	t_env		*env_list;
	t_input		*input;
}	t_shell;

// Environment
t_env	*create_env_node(t_shell *shell, char *str);
void	building_env(t_shell *shell, t_env **env_list, char **envp);
char	*set_var_value(char *str);

// Parser
int		input_checker(t_shell *shell, char *cmdline);
void	create_ctable(t_shell *shell, char *cmdline);
int		get_wordlength(t_shell *shell, char *str);
void	copy_word(char *dst, char *src, t_shell *shell, int i);
void	parse_files(t_shell *shell, t_ctable *cnode, char *cmdline);
void	parse_cmd(t_shell *shell, t_ctable *cnode, char *cmdline, int i);

bool	check_var(char *str);
int		char_check(char *str);
bool	check_var(char *str);
int		skip_quotes(char *cmdline, char quote);
int		skip_file_or_word(char *cmdline, char c, int i);
int		check_whitespace(char *str, char c);
int		finish_line(t_shell *shell);

// Bash shell
void	ft_minishell_loop(t_shell *shell, int argc, char **argv);

// Executor
void	start_execution(t_shell *shell, int i);
char	*handling_redirs(t_shell *shell, t_ctable *cnode, int node_nr);
char	*ft_connectstring(char const *s1, char const *s2, char c);
char	**ft_get_paths(t_shell *shell);
void	ft_not_found_free(t_shell *shell, char **cmds, char **paths, char **envp);
pid_t	builtin_child_exec(t_shell *shell, t_ctable *tmp, int node_nr);
int		builtin_check(t_ctable *tmp);
int		check_heredoc(t_shell *shell);

// Builtins
void	ft_mini_echo(t_shell *shell, char **cmds);
void	ft_mini_cd(t_shell *shell, char **cmds);
void	ft_mini_pwd(t_shell *shell);
void	ft_mini_export(t_shell *shell, char **cmds);
void	ft_mini_unset(t_shell *shell, char **cmds);
void	ft_mini_env(t_shell *shell, char **cmds);
void	ft_mini_exit(t_shell *shell, char **cmds);

void	ft_free_arr(char ***arr);
int		check_alpha_num(char *str);
char	*path_check(t_shell *shell, char *path);
void	ft_check_upper_dir(t_shell *shell);
void	replace_var_value(t_shell *shell, t_env *temp, char *input, int len);
char	**ft_create_export_list(t_shell *shell, t_env *tmp, int i);
char	**ft_create_env(t_shell *shell);
void	add_export_node(t_shell *shell, char *split_input);
char	*ft_get_env_value(t_env *env_list, char *str);

// Kill program
void	kill_program(t_shell *shell, char *msg, int i);
void	free_env_node(t_env **node);

void	free_cmd_list(t_ctable **head);
void	closing_fds(t_shell *shell);

// Signals
void	init_signals(t_shell *shell, int i);

// Error handling
void	handle_error(char *str, int exit_code);

#endif