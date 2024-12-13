/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/13 17:55:00 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

void	dump_chunk_datas(void *ptr)
{
	size_t	size;
	size_t	*byte;

	size = get_chunk_size(ptr);
	if (size == 0)
		size = 32;
	byte = ptr;
	while ((void *)byte < ptr + DATA_SIZE)
		printf("%zu,", *byte++);
	byte = ptr + size - DATA_SIZE;
	while ((void *)byte < ptr + size)
		printf("%zu,", *byte++);
	printf("\n");
}

void	dump_chunk(void *ptr)
{
	if (ptr)
	{
		printf("chunkptr:%p,", ptr);
		if (get_chunk_status(ptr))
			printf("usrptr:%p,", usrptr_from_chkptr(ptr));
		printf("status:%s,", get_chunk_status(ptr) == 1 ? "USED" : "FREE");
		printf("size:%zu\n", get_chunk_size(ptr));
		if (!get_chunk_status(ptr))
			dump_chunk_datas(ptr);
	}
}

void	dump_chunks(void *ptr)
{
	while (get_chunk_size(ptr))
	{
		dump_chunk(ptr);
		ptr = next_chunk(ptr);
	}
}

void	dump_page(size_t *page)
{
	if (page == NULL || header_from_page(page) == NULL)
		return ;
	while (page != NULL)
	{
		printf("page:");
		printf("%p,", page);
		printf("pp:%p,", get_page_prevpage(page));
		printf("s:%zu,", get_page_size(page));
		printf("a:%zu,", get_page_allocations(page));
		printf("np:%p\n", get_page_nextpage(page));
		page = get_next_page(page);
	}
}

void	dump_heap(void)
{
	void	*ptr;

	ptr = heap_manager(TINY);
	dump_page(ptr);
	dump_chunks(ptr);
	ptr = heap_manager(MEDIUM);
	dump_page(ptr);
	dump_chunks(ptr);
	ptr = heap_manager(LARGE);
	dump_page(ptr);
	dump_chunks(ptr);
}
