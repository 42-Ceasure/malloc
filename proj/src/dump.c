/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/17 09:09:55 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

void	dump_chunk_datas(void *ptr)
{
	size_t	size;
	size_t	*byte;

	printf("| ");
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
		printf("\t\tchunk:%p,", ptr);
		printf("size:%zu,", get_chunk_size(ptr));
		printf("status:%s\t", get_chunk_status(ptr) == 1 ? "USED" : "FREE");
		if (!get_chunk_status(ptr))
			dump_chunk_datas(ptr);
		else
		{
			printf("| userptr:%p", usrptr_from_chkptr(ptr));
			printf("\n");
		}
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
	printf("\tpage:");
	printf("%p,", page);
	printf("size:%zu,", get_page_size(page));
	printf("allocations:%zu,", get_page_allocations(page));
	printf("prevpage:%p,", get_page_prevpage(page));
	printf("nextpage:%p\n", get_page_nextpage(page));
}

void	dump_pages(void *page)
{
	if (page == NULL || header_from_page(page) == NULL)
		return ;
	while (page != NULL)
	{
		dump_page(page);
		dump_chunks(page);
		page = get_next_page(page);
	}
}

void	dump_one_heap(t_atype type)
{
	void	*ptr;

	ptr = heap_manager(type);
	printf("heap:");
	switch (type)
	{
		case TINY:
			printf("TINY\n");
			break ;
		case MEDIUM:
			printf("MEDIUM\n");
			break ;
		case LARGE:
			printf("LARGE\n");
			break ;
	}
	dump_pages(ptr);
}

void	dump_heap(void)
{
	dump_one_heap(TINY);
	dump_one_heap(MEDIUM);
	dump_one_heap(LARGE);
}
