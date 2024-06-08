#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ******************* JUST A TEST FILE *************************** //

typedef enum { 		// Dit zijn, denk ik, de verschillende cmd types die we moeten bijhouden
	t_cmd,			// Dit is gewoon de cmd + flags of arguments, bijv. 'ls -la'
	t_pipe,			// '|'
	t_greater,		// '>'
	t_d_greater,	// '>>' 
	t_less,			// '<'
	t_d_less,		// '<<'
	t_infile,		// Is de string direct na de redirect voor infiles
	t_outfile,		// Is de string direct na de redirect
}	t_type;

typedef struct s_ctable {	// ctable = command table
	t_type			type;	// Dit is het type zoals hierboven
	char			**cmds;	// Double array voor de cmd + flags of arguments
	char			*var;	// Als er in een string een '$' gevonden is, kunnen we dat hier opslaan
	struct s_ctable	*next;
}	t_ctable;

typedef struct s_shell {
	t_ctable	*cmds;		// test struct puur voor testing - Wordt vervangen door de echte shell struct
	int			len;
}	t_shell;

size_t	ft_strlen(const char *s)
{
	unsigned long	c;

	c = 0;
	while (s[c] != '\0')
		c++;
	return (c);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
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
	else if (str[i] == '\'')
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
		if (str[i] != ' ')
		{
			o++;
			if (char_check(str + i) > 0)
				i += char_check(str + i);
			else
				while (str[i] != ' ' && str[i] != '\0' && char_check(str + i) == 0)
					i++;
		}
		else
			i++;
	}
	return (o);
}

// Is zoals ft_split, maar dan aangepast voor symbolen
static int	ft_wordlength(char *str)
{
	int	i;

	i = 0;
	if (char_check(str) > 0)
	{
		i = char_check(str);
		return (i);
	}
	else
	{
		while (str[i] != ' ' && str[i] != '\0' && char_check(str + i) == 0)
			i++;
	}
	return (i);
}

// Split op dit moment de complete input, maar wordt aangepast voor de linked-list versie
char	**input_splitter(char *str)
{
	int		i;
	int		len;
	char	**split_parts;

	i = 0;
	split_parts = malloc((ft_wordcount(str) + 1) * sizeof(char *));
	if (split_parts == NULL)
		return (NULL);
	while (*str)
	{
		if (*str == ' ')
			str++;
		else
		{
			len = ft_wordlength(str);
			split_parts[i] = malloc((len + 1) * sizeof(char));
			if (split_parts[i] == NULL)
				return (ft_free(split_parts));
			ft_strlcpy(split_parts[i++], str, len + 1);
			str += len;
		}
	}
	split_parts[i] = NULL;
	return (split_parts);
}

// Deze functie is voor het aanmaken van een nieuwe ctable node die dan een deel van de input split
// in een 2d array met input_splitter in het geval van tekst, of opneemt welk symbool er gevonden is,
// of welke infile of outfile
void	create_ctable_node(t_shell *shell, char *input)
{
	int	i;
	int	wlen;

	i = 0;
	wlen = 0;
	if (input[i] == '\0')
		return (shell->len++);
	wlen = 
}

// Hier komt de while loop die nieuwe nodes aanmaakt 
void	creating_ctable(t_shell *shell, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		create_ctable_node(shell, input + i);
		i += shell->len;
		shell->len = 0;
	}
}

// Main gemaakt om de parser te testen
int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	t_ctable	*tmp;
	shell.cmds = NULL;
	shell.len = 0;

	char *input = "Hello World!| check3>> 'check 4";
	creating_ctable(&shell, argv[1]);

	int o = 0;
	tmp = shell.cmds;
	while (tmp != NULL)
	{
		while (&shell.cmds[o] != NULL)
		{
			printf("%d: %s\n", o, shell.cmds[o]);
			o++;
		}
		o = 0;
		tmp = tmp->next;
	}

	return (0);
}

