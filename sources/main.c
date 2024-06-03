/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/21 09:23:10 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/03 19:43:02 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_tools(t_tools *tools)
{
	tools->full_string = NULL;
	tools->paths = NULL;
	tools->envp = NULL;
	tools->pwd = NULL;
	tools->old_pwd = NULL;
	tools->env_list = 0;
	tools->env_list = NULL;
	tools->lexer_list = NULL;
}


int	main(int argc, char **argv, char **envp)
{
	t_tools	tools;

	if (argc != 1 || argv[1])
		kill_program(&tools, "Program does not take arguments >:(\n", 1);
	init_tools(&tools);
	building_env(&tools, &tools.env_list, envp);
	ft_minishell_loop(&tools);
	delete_list(&tools.env_list);
	return (0);
}


// int	main(int argc, char **argv, char **envp)
// {
// 	t_tools	tools;

// 	if (argc != 1 || argv[1])
// 		kill_program(&tools, "Program does not take arguments >:(\n", 1);
// 	init_tools(&tools);
// 	tools.envp = ft_copy_envp(envp);
// 	if (tools.envp == NULL) 							// toegevoegd
// 		kill_program(&tools, "envp not found!\n", 2);	// Toegevoegd
// 	ft_find_pwd(&tools);
// 	ft_init_tools(&tools);
// 	ft_minishell_loop(&tools);
// 	ft_free_2d_arr(tools.envp);
// 	return (0);
// }

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
