/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/21 09:23:10 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/05/21 16:36:23 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;
	int		i;

	if (argc != 1 || argv[1])
	{
		printf("Program does not take arguments >:(\n");
		exit(EXIT_SUCCESS);
	}
	tools.envp = ft_copy_envp(envp);
	i = 0;
	while (tools.envp[i] != NULL)
	{
		printf("%s\n", tools.envp[i]);
		i++;
	}
	ft_free_2d_arr(tools.envp);
	return (0);
}

// int	main(void)
// {
// 	int		i;
// 	int		fd;
// 	char	*line;

// 	fd = open("cat.txt", O_RDONLY);
// 	i = 1;
// 	while (i < 6)
// 	{
// 		line = get_next_line(fd);
// 		printf("Line [%02d]: %s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	line = NULL;
// 	ft_readline(line);
// 	return (0);
// }
