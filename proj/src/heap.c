/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/11/18 11:12:19 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

char heap_area[HEAP_MAX] = {'0'}; //////////////////
void *const	heap = heap_area; /////////////////

void	*mmap(void *addr,
		size_t length,
		int prot,
		int flags,
        int fd,
		off_t offset);

void	*getmap(size_t len)
{
	void	*ptr;

	ptr = mmap(	NULL,
				len,
				PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS,
				0,
				0);
	return (ptr);
}

void	*getXpages(size_t x)
{
	return (getmap(x * getpagesize()));
}

void	init_heap(void)
{
	set_chunk(heap, MAX_USABLE, CHUNK_FREE);
	set_header(heap + MAX_USABLE, 0, CHUNK_FREE);
	set_footer(heap + MAX_USABLE + END_CHUNK, 0, CHUNK_FREE);
	set_wormhole(heap, heap + MAX_USABLE);
}
