/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/11/26 14:34:31 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

t_heap *g_heap = NULL;

void	*init_area(size_t nb)
{
	void	*ptr;
	size_t	size;

	size = nb * PAGE_SIZE - END_CHUNK;
	ptr = getXpages(nb);
	set_chunk(ptr, size, CHUNK_FREE);
	set_header(ptr + size, 0, CHUNK_FREE);
	set_footer(ptr + size + END_CHUNK, 0, CHUNK_FREE);
	set_wormhole(ptr, ptr + size);
	return (ptr);
}

void	init_heap(void)
{
	static t_heap heap;

	g_heap = &heap;
	g_heap->tiny = init_area(1);
	g_heap->medium = init_area(4);
	// g_heap->large = getXpages(1);
	
	dump_heap(g_heap->tiny);
	dump_heap(g_heap->medium);
}
