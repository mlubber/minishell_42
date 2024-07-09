/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 11:01:03 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/07/09 10:53:01 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_duplicate_var(t_shell *shell, char *input)
{
	t_env	*temp;
	size_t	len;

	temp = shell->env_list;
	len = 0;
	while (input[len] != '=' && input[len] != '\0')
		len++;
	while (temp != NULL)
	{
		if (ft_strlen(temp->var_name) == len)
		{
			if (ft_strncmp(temp->var_name,
					input, ft_strlen(temp->var_name)) == 0)
			{
				if (input[len] == '=')
					replace_var_value(shell, temp, input, len);
				return (true);
			}
		}
		temp = temp->next;
	}
	return (false);
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

char	**ft_create_export_list(t_shell *shell)
{
	int		i;
	char	**export_list;
	t_env	*tmp;

	export_list = malloc((shell->env_size + 2) * sizeof(char *));
	if (export_list == NULL)
		return (NULL);
	i = 0;
	tmp = shell->env_list;
	while (i <= shell->env_size && tmp != NULL)
	{
		if (tmp->var_val == NULL)
			export_list[i++] = ft_strdup(tmp->str);
		else
			if (ft_strncmp(tmp->str, "_=", 2) != 0)
				export_list[i++] = ft_strjoin(
						ft_strjoin(tmp->var_name, "="), tmp->var_val);
		tmp = tmp->next;
	}
	export_list[i] = NULL;
	ft_sort_env_lines(export_list, i);
	return (export_list);
}

void	add_export_node(t_shell *shell, char *split_input)
{
	t_env	*tmp;
	t_env	*new;

	if (check_alpha_num(split_input) == 0)
	{
		printf("export: '%s': not a valid identifier\n", split_input);
		return ;
	}
	if (check_duplicate_var(shell, split_input) == 1)
		return ;
	else
	{
		new = create_env_node(shell, split_input);
		tmp = shell->env_list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	ft_mini_export(t_shell *shell, char **split_input)
{
	int		i;
	char	**export_list;

	if (split_input[1] != NULL)
	{
		i = 1;
		printf("%s\n", split_input[1]);
		while (split_input[i] != NULL)
			add_export_node(shell, split_input[i++]);
	}
	else
	{
		i = 0;
		export_list = ft_create_export_list(shell);
		while (export_list[i] != NULL)
			printf("declare -x %s\n", export_list[i++]);
		ft_free_arr(&export_list);
	}
	return (true);
}
