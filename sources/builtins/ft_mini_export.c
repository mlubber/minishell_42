/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 11:01:03 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/17 17:04:15 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*cut_quotes_var_val(char *str, int i)
{
	int		j;
	char	*noquotes;

	j = i;
	while (str[j] != '\0')
	{
		if (str[j] != '\"' && str[j] != '\'')
			i++;
		j++;
	}
	noquotes = malloc(i + 1 * sizeof(char));
	j = 0;
	i = 0;
	while (str[j] != '\0')
	{
		if (str[j] != '\"' && str[j] != '\'')
			noquotes[i++] = str[j];
		j++;
	}
	noquotes[i] = '\0';
	return (noquotes);
}

char	*handle_quotes_var_val(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '=')
	{
		if (str[i + 1] == '\'')
			return (str);
		else
			return (cut_quotes_var_val(str, i));
	}
	else
		return (str);
}

void	ft_free_arr(char ***arr)
{
	int	i;

	i = 0;
	if (*arr == NULL)
		return ;
	while ((*arr)[i] != NULL)
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	ft_sort_env_lines(char **envp, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (envp[i] != NULL && envp[j] != NULL)
			{
				if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
				{
					temp = envp[i];
					envp[i] = envp[j];
					envp[j] = temp;
				}
			}
			j++;
		}
		i++;
	}
}

int	check_duplicate_var(t_shell *shell, char *split_input)
{
	t_env	*temp;
	int		len;

	temp = shell->env_list;
	len = 0;
	while (split_input[len] != '=' && split_input[len] != '\0')
		len++;
	while (temp != NULL)
	{
		// printf("split_input: %s\n", split_input);
		// printf("temp->str: %s\n", temp->str);
		// printf("compare result: %d\n", ft_strncmp(temp->str, split_input, len));
		if (ft_strncmp(temp->str, split_input, len) == 0)
		{
			// printf("temp->var_val: %s\n", temp->var_val);
			// printf("split_input %s\n", split_input);
			// temp->var_val = set_var_value(split_input + len + 1);
			if (split_input[len] == '=')
			{
				temp->var_val = set_var_value(split_input + len + 1);
				temp->str = ft_dup_str(temp, split_input, len);
				if (temp->var_val == NULL)
					kill_program(shell, "Failed mallocing env var value!", 6);
			}
			else
				temp->var_val = NULL;
			return (true);
		}
		temp = temp->next;
	}
	return (false);
}

void	add_export_node(t_shell *shell, char *split_input)
{
	t_env	*tmp;
	t_env	*new;
	char	*str;

	if (check_duplicate_var(shell, split_input) == 1)
		return ;
	else
	{
		str = handle_quotes_var_val(split_input);
		new = create_env_node(shell, str);
		tmp = shell->env_list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		shell->env_size++;
	}
}
// Works fine
// *** split_input gets replaced by the command table linked list ***
int	ft_mini_export(t_shell *shell, char **split_input)
{
	int		i;
	char	**export_list;
	t_env	*tmp;

	if (split_input[1] != NULL)
	{
		i = 1;
		while (split_input[i] != NULL)
			add_export_node(shell, split_input[i++]);
	}
	else
	{
		export_list = malloc((shell->env_size + 2) * sizeof(char *));
		if (export_list == NULL)
			return (EXIT_FAILURE);
		i = 0;
		tmp = shell->env_list;
		while (i <= shell->env_size && tmp != NULL)
		{
			if (tmp->var_val == NULL)
				export_list[i] = ft_strdup(tmp->str);
			else
				export_list[i] = ft_strjoin(ft_strjoin(tmp->var_name, "="),
						tmp->var_val);
			i++;
			tmp = tmp->next;
		}
		export_list[i] = NULL;
		ft_sort_env_lines(export_list, shell->env_size + 1);
		i = 0;
		while (export_list[i] != NULL)
			printf("declare -x %s\n", export_list[i++]);
		ft_free_arr(&export_list);
	}
	return (true);
}
