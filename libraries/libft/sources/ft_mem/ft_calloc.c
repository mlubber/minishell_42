/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/15 14:22:10 by mlubbers      #+#    #+#                 */
/*   Updated: 2023/10/15 14:22:43 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*alloc;

	alloc = malloc(nitems * size);
	if (alloc == 0)
		return (0);
	ft_bzero(alloc, nitems * size);
	return (alloc);
}
