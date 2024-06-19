/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_splitter copy.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 10:48:45 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/18 14:39:53 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	checking_var(t_shell *shell, char *str)
{
	int		i;
	int		o;
	t_env	*tmp;
	char	*var;

	o = 0;
	i = 1;

	while (ft_isalnum(str[i]))
		i++;
	shell->input->cmd_len -= i;
	var = malloc(i * sizeof(char));
	if (var == NULL)
		kill_program(shell, "Failed mallocing var name", 6);
	while (o < i - 1)
	{
		var[o] = str[o + 1];
		o++;
	}
	var[o] = '\0';
	tmp = shell->env_list;
	o = 0;
	while (tmp != NULL)
	{
		if (!ft_strncmp(var, tmp->var_name, i))
		{
			shell->input->var_val = tmp->var_val;
			shell->input->cmd_len += ft_strlen(tmp->var_val) - 2;
			break ;
		}
		tmp = tmp->next;
	}
	free(var);
	return (i);
}

void	ft_copystr(char *dst, char *src, t_shell *shell)
{
	int	i;
	int	o;
	int	p;

	i = 0;
	o = 0;
	p = 1;
	while (o < shell->input->cmd_len)
	{
		if (src[i] == '\'')
		{
			i++;
			while (src[i] != '\'')
				dst[o++] = src[i++];
			i++;
		}
		else if (src[i] == '"')
		{
			i++;
			while (src[i] != '"')
			{
				if (src[i] == '$')
				{
					i += checking_var(shell, src + i);
					while (shell->input->var_val[p] != '"')
						dst[o++] = shell->input->var_val[p++];
					o++;
					p = 1;
					shell->input->var_val = NULL;
				}
				else
					dst[o++] = src[i++];
			}
			i++;
		}
		else if (src[i] == '$')
			{
				i += checking_var(shell, src + i);
				printf("TEST %s\n", shell->input->var_val);
				while (shell->input->var_val[p] != '"' && shell->input->var_val[p] != '\0')
					dst[o++] = shell->input->var_val[p++];
				o++;
				p = 1;
				shell->input->var_val = NULL;
			}
		else
			dst[o++] = src[i++];

	}
	dst[o] = '\0';
}

// In geval van leaks wordt alles opgeschoond hiermee. Alleen voor testing purposes
void	*ft_freee(char **p)
{
	int	i;

	i = 0;
	while (p[i] != NULL)
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

static int	char_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		return (1);
	else if (str[i] == '$')
		while (str[i] != ' ' && str[i] != '\0')
			i++;
	else if (str[i] == '<' || str[i] == '>')
	{
		if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
			return (2);
		return (1);
	}
	return (0);
}

// Is zoals ft_split, maar dan aangepast voor symbolen
static int	ft_wordcount(char *str)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	while (str[i])
	{
		if (ft_is_whitespace(str[i]) == 0)
		{
			if (char_check(str + i) > 0)
				return (o);
			else
				while (ft_is_whitespace(str[i]) == 0 && str[i] != '\0' && char_check(str + i) == 0)
					i++;
			o++;
		}
		else
			i++;
	}
	return (o);
}

// Berekent de lengte van elk woord, waarbij rekening wordt gehouden met quotes en variables
static int	ft_wordlength(t_shell *shell, char *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	shell->input->cmd_len = 0; // wordlength begint op 0
	if (char_check(str) > 0)
		return (0);
	else
	{
		while (!ft_is_whitespace(str[i]) && str[i] != '\0' && char_check(str + i) == 0)
		{
			if (str[i] == '\'')
			{
				i++;
				while (str[i] != '\'')
					i++;
				quotes += 2;
				i++;
			}
			else if (str[i] == '"')
			{
				i++;
				while (str[i] != '"')
				{
					if (str[i] == '$')
					{
						i += checking_var(shell, str + i);
					}
					else
						i++;
				}
				i++;
				quotes += 2;
			}
			else if (str[i] == '$')
			{
				i += checking_var(shell, str + i);
			}
			else
				i++;
		}
	}
	shell->input->cmd_len += i - quotes;
	return (i);
}

// Split programma en flags/argumentnen
char	**input_splitter(t_shell *shell, char *str)
{
	int		i;
	int		len;
	char	**split_parts;

	i = 0;
	split_parts = malloc((ft_wordcount(str) + 1) * sizeof(char *));
	if (split_parts == NULL)
		return (NULL);
	while (char_check(str + i) == 0 && str[i] != '\0')
		i++;
	shell->input->part_len = i;
	i = 0;
	while (*str)
	{
		while (ft_is_whitespace(*str))
			str++;
		if (char_check(str) > 0)
			break ;
		len = ft_wordlength(shell, str);
		split_parts[i] = malloc((shell->input->cmd_len + 1) * sizeof(char));
		if (split_parts[i] == NULL)
			return (ft_freee(split_parts)); // Huidige ft_freee hier is tijdelijk en moet worden vervangen
		ft_copystr(split_parts[i++], str, shell);
		str += len;
	}
	split_parts[i] = NULL;
	return (split_parts);
}

static int	type_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		return (t_pipe);
	else if (str[i] == '<')
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return (t_in_heredoc);
		return (t_in_file);
	}
	else if (str[i] == '>')
	{
		if (str[i] == '>' && str[i + 1] == '>')
			return (t_out_append);
		return (t_out_trunc);
	}
	return (t_cmd);
}

// Deze functie is voor het aanmaken van een nieuwe ctable node die dan een deel van de input split
// in een 2d array met input_splitter in het geval van tekst, of opneemt welk symbool er gevonden is,
// of welke infile of outfile
t_ctable	*create_ctable_node(t_shell *shell, char *cmdline)
{
	t_ctable	*new;

	new = malloc(sizeof(t_ctable));
	if (new == NULL)
		kill_program(shell, "couldn't malloc ctable node!", 6);
	if (type_check(cmdline) > 0)
	{
		new->type = type_check(cmdline);
		// new->file = NULL;
		// if (new->type == t_less || new->type == t_d_less)
		// 	new->file = get_file_name(shell, cmdline);
		// else if (new->type == t_greater || new->type == t_d_greater)
		// 	new->file = get_file_name(shell, cmdline);
		// new->cmds = NULL;
		// if (new->type == t_pipe)
		// 	shell->input->part_len = 1;
	}
	else
	{
		new->type = t_cmd;
		new->cmds = input_splitter(shell, cmdline);
	}
	new->next = NULL;
	return (new);
}

// Hier wordt de command table gemaakt
void	create_ctable(t_shell *shell, char *cmdline)
{
	int			i;
	t_ctable	*tmp;
	t_ctable	*new;

	i = 0;
	tmp = shell->input->cmds;
	while (ft_is_whitespace(cmdline[i]))
		i++;
	get_files(shell, cmdline);
	shell->input->cmds = create_ctable_node(shell, cmdline + i);
	i += shell->input->part_len;
	tmp = shell->input->cmds;
	while (cmdline[i])
	{
		while (ft_is_whitespace(cmdline[i]))
			i++;
		if (cmdline[i] == '\0')
			break ;
		new = create_ctable_node(shell, cmdline + i);
		tmp->next = new;
		if (tmp->next == NULL)
			kill_program(shell, "Failed creating cmd node!", 6); // PLACEHOLDER KILL_PROGRAM
		tmp = tmp->next;
		i += shell->input->part_len;
		shell->input->part_len = 0;
	}
}
