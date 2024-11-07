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

char	heap[HEAP_MAX] = {'0'};

void	dump_chunk(size_t *chunk)
{
	printf("address:%p,", chunk);
	printf("used:%d,", is_chunk_free(chunk));
	printf("size:%zu\n", get_chunk_size(chunk));
}

void	dump_heap(void)
{
	size_t	*ptr;

	ptr = (size_t *)heap;
	printf("heap state :\n");
	while (get_chunk_size(ptr))
	{
		dump_chunk((size_t *)ptr);
		ptr = next_chunk((char *)ptr);
	}
}

void	init_heap(void)
{
	size_t	*i;

	i = (size_t *)heap;
	create_block(i, MAX_USABLE, CHUNK_FREE);
	i = (size_t *)(heap + MAX_USABLE);
	create_block(i, 0, CHUNK_FREE);
}
