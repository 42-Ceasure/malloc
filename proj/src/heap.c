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

char heap_area[HEAP_MAX] = {'0'};
void *const	heap = heap_area;

void	init_heap(void)
{
	set_chunk(heap, MAX_USABLE, CHUNK_FREE);
	set_chunk(heap + MAX_USABLE, 0, CHUNK_FREE);
	set_wormhole(heap, heap + MAX_USABLE);
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

void	dump_byte(char byte)
{
	printf("%x%x", ((byte & 0xF0) >> 4), ((byte & 0x0F) >> 4));
}

void	dump_chunk_datas(void *ptr)
{
	size_t	i;
	size_t	size;
	char	*byte;

	i = 0;
	size = get_chunk_size(ptr);
	if (size > 256)
		return ;
	byte = usrptr_from_chunk(ptr);
	printf("%zu,", size);
	if (!is_chunk_used(ptr))
		printf("%zu,", get_chunk_size(byte));
	while (i < size - DATA_SIZE)
		dump_byte(byte[i++]);
	printf(",%zu\n", size);
}

void	dump_chunk(void *ptr)
{
	if (ptr)
	{
		printf("chunkptr:%p,", ptr);
		printf("usrptr:%p,", usrptr_from_chunk(ptr));
		printf("status:%s,", is_chunk_used(ptr) == 1 ? "USED" : "FREE");
		printf("size:%zu\n", get_chunk_size(ptr));
		// dump_chunk_datas(ptr);
	}
}
