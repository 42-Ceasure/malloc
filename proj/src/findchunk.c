/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cpy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/10/25 10:55:12 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

void	*next_chunk(char *ptr)
{
	t_chunk chunk;

	chunk.ptr = (size_t *)ptr;
	chunk.size = *chunk.ptr & NBR;
	return (ptr + chunk.size);
}

void	*find_ffit_chunk(size_t *ptr, size_t size)
{
	ptr = (size_t *)heap;
	while (get_chunk_size(ptr))
	{
		if (!is_chunk_free(ptr) && get_chunk_size(ptr) >= size)
			return (ptr);
		ptr = next_chunk((char *)ptr);
	}
	return (NULL);
}
