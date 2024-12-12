/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/12 11:58:06 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

t_heap *g_heap = NULL;

void	init_chunk(void *ptr, size_t size)
{
	size = size - END_CHUNK;
	set_chunk(ptr, size, CHUNK_FREE);
	set_header(ptr + size, 0, CHUNK_FREE);
	set_footer(ptr + size + END_CHUNK, 0, CHUNK_FREE);
	set_wormhole(ptr, ptr + size);
}

void	init_chunks(void)
{
	init_chunk(g_heap->tiny, get_page_size(g_heap->tiny));
	init_chunk(g_heap->medium, get_page_size(g_heap->medium));
	init_chunk(g_heap->large, get_page_size(g_heap->large));
}

void	init_pages(void)
{
	g_heap->tiny = new_page(DEFAULT_TINY);
	g_heap->medium = new_page(DEFAULT_MEDIUM);
	g_heap->large = new_page(DEFAULT_LARGE);
}

void	init_heap(void)
{
	static	t_heap heap;

	g_heap = &heap;
	init_pages();
	dump_page(g_heap->tiny);
	dump_page(g_heap->medium);
	dump_page(g_heap->large);
	init_chunks();
	dump_heap(g_heap->tiny);
	dump_heap(g_heap->medium);
	dump_heap(g_heap->large);
}
