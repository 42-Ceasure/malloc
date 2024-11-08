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

void	init_heap(void)
{
	void	*i;

	// maybe init with size of memory to get rid of MAX_USABLE
	i = heap;
	set_chunk(i, MAX_USABLE, CHUNK_FREE);
	i = heap + MAX_USABLE;
	set_chunk(i, 0, CHUNK_FREE);
}

void	dump_heap(void)
{
	void	*ptr;

	ptr = heap; // as for mymalloc, this will be soon given by the system.
	// I will need to think passing area to that function
	printf("heap state :\n");
	while (ptr)
	{
		dump_chunk(ptr);
		ptr = next_chunk(ptr);
	}
}

void	dump_chunk(void *ptr)
{
	if (ptr)
	{
		printf("address:%p,", ptr);
		printf("used:%d,", is_chunk_free(ptr));
		printf("size:%zu\n", get_chunk_size(ptr));
	}
}
