/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 09:22:42 by mlubbers      #+#    #+#                 */
/*   Updated: 2023/10/23 14:08:30 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*substr;
	char	*newstr;
	size_t	strlen;
	size_t	i;

	strlen = ft_strlen(str);
	if (start > ft_strlen(str))
		return (ft_strdup(""));
	if (start + len < strlen)
		substr = (char *)malloc((len + 1) * sizeof(char));
	else
		substr = (char *)malloc((strlen - start + 1) * sizeof(char));
	if (substr == 0)
		return (0);
	i = start;
	newstr = substr;
	while ((i < start + len) && str[i])
	{
		*newstr = str[i];
		i++;
		newstr++;
	}
	*newstr = '\0';
	return (substr);
}
