/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_env_node.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 14:38:18 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/08 15:35:24 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// char	*ft_dup_str(t_env *node, char *str, int i)
// {
// 	char	*result;
// 	char	*single_quote_str;

// 	single_quote_str = ft_strdup(str + i + 1);
// 	if (node->var_val != NULL)
// 	{
// 		if (single_quote_str[0] == '\'' && single_quote_str[1] == '\"')
// 			result = ft_strjoin(ft_strjoin(node->var_name, "="),
// 					ft_strtrim(single_quote_str, "\'"));
// 		else if (single_quote_str[0] == '\"' && single_quote_str[1] == '\'')
// 			result = ft_strjoin(ft_strjoin(node->var_name, "="),
// 					ft_strtrim(single_quote_str, "\""));
// 		else
// 			result = ft_strjoin(ft_strjoin(node->var_name, "="),
// 					ft_strtrim(node->var_val, "\""));
// 	}
// 	else
// 		result = ft_strdup(str);
// 	return (result);
// }

static char	*set_var_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	var_name = malloc((i + 1) * sizeof(char));
	if (var_name == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		var_name[i] = str[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}


static char	*set_var_value_quotes(char *str)
{
	int		i;
	int		o;
	char	*var_value;

	i = 0;
	o = 0;
	while (str[i])
		i++;
	var_value = malloc((i + 3) * sizeof(char));
	if (var_value == NULL)
		return (NULL);
	var_value[0] = '"';
	var_value[i + 1] = '"';
	var_value[i + 2] = '\0';
	i = 1;
	while (str[o] != '\0')
	{
		var_value[i] = str[o];
		i++;
		o++;
	}
	return (var_value);
}

char	*set_var_value(char *str)
{
	// int		i;
	char	*var_value;

	// if (*str == '"')
	// {
	// 	i = 1;
	// 	while (str[i] != '"' && str[i] != '\0')
	// 		i++;
	// 	if (str[i] == '"')
	// 		var_value = malloc((i + 2) * sizeof(char));
	// 	else
	// 		return (NULL);
	// 	i = 0;
	// 	while (var_value != NULL && str[i] != '\0')
	// 	{
	// 		var_value[i] = str[i];
	// 		i++;
	// 	}
	// }
	// else
	var_value = set_var_value_quotes(str);
	if (var_value == NULL)
		return (NULL);
	return (var_value);
}

static void	init_node(t_shell *shell, t_env *node, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '=')
	{
		node->var_val = set_var_value(str + i + 1);
		if (node->var_val == NULL)
			kill_program(shell, "Failed mallocing env var value!", 6);
	}
	else
		node->var_val = NULL;
	node->var_name = set_var_name(str);
	if (node->var_name == NULL)
		kill_program(shell, "Failed mallocing env name in env node!", 6);
	node->str = ft_strdup(str);
	if (node->str == NULL)
		kill_program(shell, "Failed dupping str for env node!", 6);
	node->printed = false;
	node->node_num = shell->env_size;
}

t_env	*create_env_node(t_shell *shell, char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		kill_program(shell, "Failed mallocing env node!", 6);
	node->next = NULL;
	node->str = NULL;
	node->var_name = NULL;
	node->var_val = NULL;
	init_node(shell, node, str);
	shell->env_size++;
	if (node->var_name == NULL)
		kill_program(shell, "Failed mallocing node!", 3);
	return (node);
}
