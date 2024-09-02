/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 12:10:52 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/09/02 13:43:08 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	search_and_delete_var(t_shell *shell, char *str)
{
	t_env	*temp;
	t_env	*prev;

	temp = shell->env_list;
	prev = NULL;
	if (temp != NULL
		&& ft_strncmp(temp->var_name, str, ft_strlen(str) + 1) == 0)
	{
		shell->env_list = temp->next;
		free_env_node(&temp);
		temp = NULL;
		return (true);
	}
	while (temp != NULL
		&& ft_strncmp(temp->var_name, str, ft_strlen(str) + 1) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (false);
	prev->next = temp->next;
	free_env_node(&temp);
	return (true);
}

static void	check_if_oldpwd(t_shell *shell, char *str)
{
	int		i;
	char	*oldpwd;

	i = 0;
	oldpwd = "OLDPWD";
	while (str[i])
	{
		if (str[i] != oldpwd[i])
			return ;
		i++;
	}
	if (str[i] != oldpwd[i])
		return ;
	free(shell->old_pwd);
	shell->old_pwd = NULL;
}

void	ft_mini_unset(t_shell *shell, char **split_input)
{
	int		i;
	t_env	*tmp;

	i = 1;
	tmp = shell->env_list;
	if (split_input[1] == NULL)
		return ;
	while (split_input[i] != NULL)
	{
		check_if_oldpwd(shell, split_input[i]);
		if (search_and_delete_var(shell, split_input[i]) != 0)
		{
			shell->env_size--;
			tmp = shell->env_list;
		}
		i++;
	}
}
