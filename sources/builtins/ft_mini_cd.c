/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/04 09:00:37 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/25 13:31:00 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	add_node_middle(t_shell *shell, t_env **head, int position, char *str)
{
	t_env	*new;
	t_env	*tmp;

	new = create_env_node(shell, str);
	if (position == 1)
	{
		new->next = *head;
		*head = new;
	}
	else
	{
		tmp = *head;
		while (position > 1)
		{
			tmp = tmp->next;
			position--;
		}
		new->next = tmp->next->next;
		tmp->next = new;
	}
}

void	ft_change_path_in_env(t_shell *shell)
{
	t_env	*temp_list;
	int		i;

	temp_list = shell->env_list;
	while (temp_list->next != NULL)
	{
		i = 0;
		if (ft_strncmp(temp_list->next->str, "PWD=", 4) == 0)
		{
			temp_list->next->str = ft_strjoin("PWD=", shell->pwd);
			while (temp_list->next->str[i] != '=')
				i++;
			temp_list->next->var_val
				= set_var_value(temp_list->next->str + i + 1);
		}
		else if (ft_strncmp(temp_list->next->str, "OLDPWD=", 7) == 0)
		{
			temp_list->next->str = ft_strjoin("OLDPWD=", shell->old_pwd);
			while (temp_list->next->str[i] != '=')
				i++;
			temp_list->next->var_val
				= set_var_value(temp_list->next->str + i + 1);
		}
		temp_list = temp_list->next;
	}
}

char	*ft_get_env_value(t_env *env_list, char *str)
{
	t_env	*tmp;
	int		i;

	tmp = env_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->str, str, ft_strlen(str)) == 0)
		{
			i = 0;
			while (tmp->str[i] != '=')
				i++;
			if (ft_strncmp("OLDPWD=", str, ft_strlen(str)) == 0)
				printf("%s\n", tmp->str + i + 1);
			return (tmp->str + i + 1);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_get_full_path(t_env *env_list, char *str)
{
	char	*home;
	// char	*path;
	char	*join;

	home = ft_get_env_value(env_list, "HOME=");
	// path = ft_strdup(str + 1);
	join = ft_strjoin(home, str + 1);
	// free(path);
	return (join);
}

int	ft_change_directory(t_shell *shell, char **split_input)
{
	int	ret;

	if (split_input[1] == NULL
		|| (split_input[1][0] == '~' && split_input[1][1] == '\0'))
		ret = chdir(ft_get_env_value(shell->env_list, "HOME="));
	else if (split_input[1][0] == '-' && split_input[1][1] == '\0')
		ret = chdir(ft_get_env_value(shell->env_list, "OLDPWD="));
	else if (split_input[1][0] == '~' && split_input[1][1] != '\0')
		ret = chdir(ft_get_full_path(shell->env_list, split_input[1]));
	else
		ret = chdir(split_input[1]);
		
	return (ret);
}

// Works like the 'cd' function. Using 'cd' or 'cd sources' work, for example
// NOT FINISHED: input 'cd ..' gives segvaults.
// *** split_input gets replaced by the command table linked list ***
int	ft_mini_cd(t_shell *shell, char **split_input)
{
	int		ret;

	if (split_input[1] != NULL && split_input[2] != NULL)
	{
		printf("cd: Too many arguments");
		return (1);
	}
	ret = ft_change_directory(shell, split_input);
	if (ret == -1)
		ft_putendl_fd("Error: No such file or directory", STDERR_FILENO);
	free (shell->old_pwd);
	shell->old_pwd = shell->pwd;
	shell->pwd = getcwd(NULL, 0);
	if (shell->pwd == NULL)
		kill_program(shell, "Error: getcwd failed", 6);
	ft_change_path_in_env(shell);
	return (1);
}
