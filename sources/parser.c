#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// ******************* JUST A TEST FILE *************************** //

typedef enum { 		// Dit zijn, denk ik, de verschillende cmd types die we moeten bijhouden
	t_cmd,			// Dit is gewoon de cmd + flags of arguments, bijv. 'ls -la'
	t_pipe,			// '|'
	t_less,			// '<'
	t_d_less,		// '<<'
	t_greater,		// '>'
	t_d_greater,	// '>>' 
}	t_type;

typedef struct s_env
{
	char			*str;
	char			*var_name;
	char			*var_val;
	bool			printed;
	int				node_num;
	struct s_env	*next;
}	t_env;

typedef struct s_ctable {	// ctable = command table
	t_type			type;	// Dit is het type zoals hierboven
	char			**cmds;	// Double array voor de cmd + flags of arguments
	char			*var;	// Als er in een string een '$' gevonden is, kunnen we dat hier opslaan
	int				var_len;
	char			*file;	// Filenaam als er een redirect gevonden is
	struct s_ctable	*next;
}	t_ctable;


typedef struct s_input
{
	t_ctable	*cmds;
	char		*var_val;
	int			var_len;
}	t_input;

typedef struct s_shell {
	t_input		*input;		// test struct puur voor testing - Wordt vervangen door de echte shell struct
	bool		infile;
	bool		outfile;
	int			len;
	t_env		*env_list;
}	t_shell;

int	ft_is_whitespace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

size_t	ft_strlen(const char *s)
{
	unsigned long	c;

	c = 0;
	while (s[c] != '\0')
		c++;
	return (c);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size, t_shell *shell)
{
	size_t	i;
	size_t	o;

	i = 0;
	o = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1)
	{
		if (src[i] == '"') // FIXXXXEEEEEEEEEEEEEEEE DIT
			i++;
		dst[o] = src[i];
		i++;
		o++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

// In geval van leaks wordt alles opgeschoond hiermee. Alleen voor testing purposes
void	*ft_free(char **p)
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

// Dit checkt de quotes van begin tot eind en returned de length. Moet aangepast worden
// aan hoe bash werkt. Bijv.: ex"i"t wordt in bash gewoon exit en zou bash moeten afsluiten
static int	check_quotes(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
	{
		while (str[i] != '\'' && str[i] != '\0')
			i++;
		if (str[i] != '\'')
			return (-1);
		return (i);
	}
	else if (str[i] == '"')
	{
		while (str[i] != '"' && str[i] != '\0')
			i++;
		if (str[i] != '"')
			return (-1);
		return (i);
	}
	return (0);
}

// checked vanaf een bepaald punt in de string of een bepaald symbool gevonden wordt
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
	else if (str[i] == '\'' || str[i] == '"') // Moet hier wss weg omdat quotes wel tussen tekst moet staan
		return (check_quotes(str));
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


int	checking_var(t_shell *shell, char *str)
{
	int		i;
	t_env	*tmp;

	i = 1;
	while (ft_isalnum(str + 1))
		i++;
	shell->input->var_len = i;
	tmp = shell->env_list;
	while (shell->env_list != NULL)
	{
		if (ft_strncmp(str + 1, tmp->var_name, i + 1))
			shell->input->var_val = tmp->var_val;

	}
}


// Is zoals ft_split, maar dan aangepast voor symbolen
static int	ft_wordlength(t_shell *shell, char *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	if (char_check(str) > 0)
	{
		i = char_check(str);
		return (i);
	}
	else
	{
		while (!ft_is_whitespace(str[i]) && str[i] != '\0' && char_check(str + i) == 0)
		{
			if (str[i] == '\'')
				while (str[i] != '\'')
					i++;
			if (str[i] == '$')
				i += checking_var(shell, str + i);
			i++;
		}
	}
	return (i - quotes * 2);
}

// Split op dit moment de complete input, maar wordt aangepast voor de linked-list versie
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
	shell->len = i;
	i = 0;
	while (*str)
	{
		while (ft_is_whitespace(*str))
			str++;
		if (char_check(str) > 0)
			break ;
		len = ft_wordlength(shell, str);
		split_parts[i] = malloc((len + 1) * sizeof(char));
		if (split_parts[i] == NULL)
			return (ft_free(split_parts));
		ft_strlcpy(split_parts[i++], str, len + 1);
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
			return (t_d_less);
		return (t_less);
	}
	else if (str[i] == '>')
	{
		if (str[i] == '>' && str[i + 1] == '>')
			return (t_d_greater);
		return (t_greater);
	}
	return (t_cmd);
}

char	*get_file_name(t_shell *shell, char *input)
{
	int		i;
	int		o;
	char	*file;

	i = 0;
	o = 0;
	while (input[i] == '<' || input[i] == '>' || ft_is_whitespace(input[i]))
		i++;
	while (ft_is_whitespace(input[i + o]) == 0 && char_check(input + i + o) == 0)
		o++;
	shell->len = i + o;
	file = malloc((o + 1) * sizeof(char));
	ft_strlcpy(file, input + i, o + 1);
	return (file);
}


// Deze functie is voor het aanmaken van een nieuwe ctable node die dan een deel van de input split
// in een 2d array met input_splitter in het geval van tekst, of opneemt welk symbool er gevonden is,
// of welke infile of outfile
t_ctable	*create_ctable_node(t_shell *shell, char *input)
{
	t_ctable	*new;

	new = malloc(sizeof(t_ctable));
	if (new == NULL)
		exit(6); // PLACEHOLDER KILL_PROGRAM
	if (type_check(input) > 0)
	{
		new->type = type_check(input);
		new->file = NULL;
		if (new->type == t_less || new->type == t_d_less)
			new->file = get_file_name(shell, input);
		else if (new->type == t_greater || new->type == t_d_greater)
			new->file = get_file_name(shell, input);
		new->cmds = NULL;
		new->var = NULL;
		if (new->type == t_pipe)
			shell->len = 1;
	}
	else
	{
		new->type = t_cmd;
		new->cmds = input_splitter(shell, input);
		new->var = NULL; // TO BE HANDLED IN NEW FUNCTIONS
	}
	new->next = NULL;
	return (new);
}


// Hier komt de while loop die nieuwe nodes aanmaakt 
void	creating_ctable(t_shell *shell, char *input)
{
	int			i;
	t_ctable	*tmp;
	t_ctable	*new;

	i = 0;
	tmp = shell->input->cmds;
	while (ft_is_whitespace(input[i]))
		i++;
	shell->input->cmds = create_ctable_node(shell, input + i);
	i += shell->len;
	tmp = shell->input->cmds;
	while (input[i])
	{
		while (ft_is_whitespace(input[i]))
			i++;
		if (input[i] == '\0')
			break ;
		new = create_ctable_node(shell, input + i);
		tmp->next = new;
		if (tmp->next == NULL)
			exit(6); // PLACEHOLDER KILL_PROGRAM
		tmp = tmp->next;
		i += shell->len;
		shell->len = 0;
	}
}

// Main gemaakt om de parser te testen
int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_ctable	*tmp;

	shell.input->cmds = NULL;
	shell.len = 0;
	shell.infile = false;
	shell.outfile = false;
	char *input = "Hello World! | check >> check4";
	creating_ctable(&shell, input);

	int o = 0;
	tmp = shell.input->cmds;
	while (tmp != NULL)
	{
		printf("NODE:\n");
		while (tmp->cmds != NULL && tmp->cmds[o] != NULL)
		{
			if (tmp->cmds != NULL)
				printf("string %d: %s\n", o, tmp->cmds[o]);
			o++;
		}
		if (tmp->file != NULL)
			printf("file %d: %s\n", o, tmp->file);
		printf("Type: %d\n", tmp->type);
		printf("\n");
		o = 0;
		tmp = tmp->next;
	}
	return (0);
}

