/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/09 08:55:50 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/04 16:33:47 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	ft_readline(char *line)
// {
// 	line = readline("\nEnter something: ");
// 	if (line == NULL)
// 		printf("No input recieved.\n");
// 	else if (*line == '\0')
// 		printf("String is empty.\n");
// 	else
// 	{
// 		printf("You entered: %s\n", line);
// 		add_history(line);
// 		free(line);
// 	}
// }


// char	**ft_copy_envp(char **envp)
// {
// 	char	**envp_copy;
// 	size_t	i;

// 	i = 0;
// 	while (envp[i] != NULL)
// 		i++;
// 	envp_copy = ft_calloc(i + 1, sizeof(char *));
// 	if (envp_copy == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		envp_copy[i] = ft_strdup(envp[i]);
// 		if (envp_copy[i] == NULL)
// 		{
// 			ft_free_2d_arr(envp_copy);
// 			return (NULL); // Veranderd van 'return (envp_copy)'
// 		}
// 		i++;
// 	}
// 	return (envp_copy);
// }
