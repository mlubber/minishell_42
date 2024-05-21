/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 10:20:17 by mlubbers      #+#    #+#                 */
/*   Updated: 2023/10/16 11:50:34 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	totlen;
	char	*newstr;

	totlen = ((ft_strlen(s1) + 1) + ft_strlen(s2));
	newstr = (char *)malloc(totlen * sizeof(char));
	if (!newstr)
		return (0);
	ft_strlcpy(newstr, s1, (ft_strlen(s1) + 1));
	ft_strlcat(newstr, s2, totlen);
	return (newstr);
}
