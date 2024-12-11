/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/11 12:52:55 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

t_heap *g_heap = NULL;

void	*init_chunks(void *ptr, size_t size)
{
	size = size - END_CHUNK;
	set_chunk(ptr, size, CHUNK_FREE);
	set_header(ptr + size, 0, CHUNK_FREE);
	set_footer(ptr + size + END_CHUNK, 0, CHUNK_FREE);
	set_wormhole(ptr, ptr + size);
	return (ptr);
}

void	init_heap(void)
{
	static	t_heap heap;
	void	*page;

	g_heap = &heap;
	page = new_page(1);
	dump_page(page);
	g_heap->tiny = init_chunks(page, get_page_freespace(page));
	page = new_page(4);
	dump_page(page);
	g_heap->medium = init_chunks(page, get_page_freespace(page));
	page = new_page(1);
	g_heap->large = init_chunks(page, get_page_freespace(page));
	dump_page(page);
	dump_heap(g_heap->tiny);
	dump_heap(g_heap->medium);
	dump_heap(g_heap->large);
}
