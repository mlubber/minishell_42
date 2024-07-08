/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   copy_word.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/26 15:38:48 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/08 12:19:09 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	copy_var(char *dst, char *var_value, t_copy *pos)
{
	int	i;

	i = 1;
	while (var_value[i] != '"')
		dst[pos->dest++] = var_value[i++];
}

static int	get_var_value(t_shell *shell, char *dst, char *src, t_copy *pos)
{
	int		i;
	t_env	*tmp;
	char	*var_name;

	i = 1;
	while (ft_isalnum(src[i]) || src[i] == '_')
		i++;
	var_name = malloc(i * sizeof(char));
	if (var_name == NULL)
		kill_program(shell, "Failed mallocing var name in copy_var", 6);
	ft_strlcpy(var_name, src + 1, i);
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
	copy_var(dst, tmp->var_val, pos);
	return (i);
}

static int	check_var(t_shell *shell, char *dst, char *src, t_copy *pos)
{
	int		i;
	char	*exit_code;

	i = 0;
	if (src[1] == '?')
	{
		exit_code = ft_itoa(shell->exit_code);
		while (exit_code[i] != '\0')
			dst[pos->dest++] = exit_code[i++];
		free (exit_code);
		return (2);
	}
	else
		return (get_var_value(shell, dst, src, pos));
}

static void	handle_quotes(t_shell *shell, char *dst, char *src, t_copy *pos)
{
	pos->src++;
	while (src[pos->src] != pos->quote)
	{
		if (pos->quote == '"' && src[pos->src] == '$')
			pos->src += check_var(shell, dst, src + pos->src, pos);
		else
			dst[pos->dest++] = src[pos->src++];
	}
	pos->src++;
}

void	copy_word(char *dst, char *src, t_shell *shell)
{
	t_copy	pos;

	pos.src = 0;
	pos.dest = 0;
	pos.quote = 0;
	while (pos.dest < shell->input->word_len)
	{
		if (src[pos.src] == '\'')
		{
			pos.quote = '\'';
			handle_quotes(shell, dst, src, &pos);
		}
		else if (src[pos.src] == '"')
		{
			pos.quote = '"';
			handle_quotes(shell, dst, src, &pos);
		}
		else if (src[pos.src] == '$')
			pos.src += check_var(shell, dst, src + pos.src, &pos);
		else
			dst[pos.dest++] = src[pos.src++];
	}
	dst[pos.dest] = '\0';
}
