/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/21 09:23:10 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/05/30 17:58:04 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;

	if (argc != 1 || argv[1])
		kill_program(&tools, "Program does not take arguments >:(\n", 1);
	tools.envp = ft_copy_envp(envp);
	if (tools.envp == NULL) 							// toegevoegd
		kill_program(&tools, "envp not found!\n", 2);	// Toegevoegd
	ft_find_pwd(&tools);
	ft_init_tools(&tools);
	ft_minishell_loop(&tools);
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
