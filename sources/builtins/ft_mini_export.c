/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 11:01:03 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/25 15:40:52 by mlubbers      ########   odam.nl         */
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
		if (str[i + 1] == '\'' && str[i + 2] == '\"')
			return (str);
		if (str[i + 1] == '\"' && str[i + 2] == '\'')
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

void	replace_var_value(t_shell *shell, t_env *temp, char *input, int len)
{
	char	*str;

	str = handle_quotes_var_val(input);
	temp->var_val = set_var_value(str + len + 1);
	temp->str = ft_dup_str(temp, str, len);
	if (temp->var_val == NULL)
		kill_program(shell, "Failed mallocing env var value!", 6);
}

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

// int	compare_var(t_shell *shell, char *str)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	while (str[len] != '=' && str[len] != '\0')
// 		len++;
// 	while (i < len && str[i] == shell->env_list->str[i])
// 		i++;
// 	if (str[i] != shell->env_list->str[i])
// 		return (0);
// 	return (len);
// }

// int	check_duplicate_var(t_shell *shell, char *input)
// {
// 	t_env	*temp;
// 	t_env	*temp_node;
// 	int		x;
// 	int		len;

// 	temp = shell->env_list;
// 	while (temp != NULL)
// 	{
// 		len = compare_var(shell, input);
// 		if (len > 0 && input[len] == '=')
// 		{
// 			x = temp->next->node_num;
// 			temp_node = temp->next;
// 			add_node_middle(shell, &shell->env_list, x, input);
// 			free_env_node(&temp_node);
// 			return (true);
// 		}
// 		temp = temp->next;
// 	}
// 	return (false);
// }
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

int	check_alpha_num(char *str)
{
	int	i;

	i = 0;
	if ((str[i] >= 'a' && str[i] <= 'z')
		|| (str[i] >= 'A' && str[i] <= 'Z')
		|| (str[i] == '_'))
	{
		i++;
		while (str[i] != '=' && str[i] != '\0')
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

void	add_export_node(t_shell *shell, char *split_input)
{
	t_env	*tmp;
	t_env	*new;
	char	*str;

	if (check_alpha_num(split_input) == 0)
	{
		printf("export: '%s': not a valid identifier\n", split_input);
		return ;
	}
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
	}
}
// Works fine
// *** split_input gets replaced by the command table linked list ***
int	ft_mini_export(t_shell *shell, char **split_input)
{
	int		i;
	char	**export_list;

	if (split_input[1] != NULL)
	{
		i = 1;
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
