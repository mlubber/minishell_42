/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_wordlength.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/26 16:36:58 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/08 16:23:13 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exit_code_len(t_shell *shell)
{
	char	*exit_code;

	exit_code = ft_itoa(shell->exit_code);
	shell->input->word_len = ft_strlen(exit_code);
	free (exit_code);
	return (2);
}

static int	get_var_val_len(t_shell *shell, char *str)
{
	int		i;
	t_env	*tmp;
	char	*var_name;

	i = 1;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	shell->input->word_len -= i;
	var_name = malloc(i * sizeof(char));
	if (var_name == NULL)
		kill_program(shell, "Failed mallocing var name in copy_var", 6);
	ft_strlcpy(var_name, str + 1, i);
	tmp = shell->env_list;
	while (tmp != NULL)
	{
		if (!ft_strncmp(var_name, tmp->var_name, i))
			break ;
		tmp = tmp->next;
	}
	free(var_name);
	if (tmp == NULL)
		return (i);
	if (tmp->var_val != NULL)
		shell->input->word_len += ft_strlen(tmp->var_val) - 2;
	return (i);
}

static int	check_var(t_shell *shell, char *str)
{
	int	i;

	i = 1;
	if (str[i] == '?')
		return (exit_code_len(shell));
	else
		return (get_var_val_len(shell, str));
}

static int	handle_quotes(t_shell *shell, char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] != quote)
	{
		if (quote == '"' && str[i] == '$')
			i += check_var(shell, str + i);
		else
			i++;
	}
	i++;
	shell->input->word_len -= 2;
	return (i);
}

int	get_wordlength(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	shell->input->word_len = 0;
	while (str[i] != '\0' && !check_whitespace(NULL, str[i]) && char_check(str + i) == 0)
	{
		if (str[i] == '\'')
			i += handle_quotes(shell, str + i, '\'');
		else if (str[i] == '"')
			i += handle_quotes(shell, str + i, '"');
		else if (str[i] == '$')
			i += check_var(shell, str + i);
		else
			i++;
	}
	shell->input->word_len += i;
	return (i);
}
