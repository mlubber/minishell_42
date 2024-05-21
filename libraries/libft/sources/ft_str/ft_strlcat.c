/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 11:59:03 by mlubbers      #+#    #+#                 */
/*   Updated: 2023/10/16 10:11:43 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	offset;
	int		i;

	dst_len = ft_strlen(dst);
	offset = dst_len;
	i = 0;
	if (dstsize < dst_len + 1)
		return (ft_strlen(src) + dstsize);
	if (dstsize > dst_len + 1)
	{
		while (src[i] && offset < dstsize - 1)
		{
			dst[offset] = src[i];
			offset++;
			i++;
		}
		dst[offset] = '\0';
	}
	return (dst_len + ft_strlen(src));
}
