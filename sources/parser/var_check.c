/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/24 12:49:20 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/24 14:32:42 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



char	*var_expander(t_shell *shell, char *input)
{
	int		len;
	char	*new_line;

	len = get_new_len(input);
	new_line = malloc((len + 1) * sizeof(char));
}

char	*var_check(t_shell *shell, char **input)
{
	int		i;
	bool	var;

	i = 0;
	var = false;
	while (*input[i])
	{
		if (*input[i] == '\'')
			while (*input[i] != '\'')
				i++;
		if (*input[i] == '$')
			var = true;
		if (*input[i] != '\0')
			i++;
	}
	if (var == true)
		*input = var_expander(shell, *input);
	return (input);
}
