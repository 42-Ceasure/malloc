/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/12 12:00:54 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

void	*getmap(const size_t len)
{
	void	*map;

	map = mmap(	NULL,
				len,
				PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS,
				0,
				0);
	return (map);
}

void	set_page_size(size_t *page, size_t size)
{
	*(page + SIZE) = size - PAGE_HEADSIZE;
}
void	set_page_allocations(size_t *page, size_t allocations)
{
	*(page + ALLOC) = allocations;
}
void	set_page_nextpage(size_t *page, size_t *nextpage)
{
	write_adress((page + NEXTP), nextpage);
}
void	set_page_prevpage(size_t *page, size_t *prevpage)
{
	write_adress((page + PREVP), prevpage);
}

size_t	get_page_size(size_t *page)
{
	return (*(page + SIZE));
}
size_t	get_page_allocations(size_t *page)
{
	return (*(page + ALLOC));
}
void	*get_page_nextpage(size_t *page)
{
	return (get_adress(page + NEXTP));
}
void	*get_page_prevpage(size_t *page)
{
	return (get_adress(page + PREVP));
}

void	init_page(void *page, size_t size)
{
	set_page_size(page, size);
	set_page_allocations(page, 0);
	set_page_nextpage(page, NULL);
	set_page_prevpage(page, NULL);
}

void	*header_from_page(void *page)
{
	return (page - PAGE_HEADSIZE);
}
void	*page_from_header(void *page)
{
	return (page + PAGE_HEADSIZE);
}

void	link_pages(void *page1, void *page2)
{
	set_page_nextpage(page1, page2);
	set_page_prevpage(page2, page1);
}

void	*extend_page(void *page, size_t nb)
{
	void	*new;

	new = new_page(nb);
	link_pages(page, new);
	return (new);
}

void	*new_page(size_t nb)
{
	void	*page;
	size_t	size;

	size = nb * PAGE_SIZE;
	page = page_from_header(getmap(size));
	init_page(page, size);
	return (page);
}

void	*get_next_page(void *page)
{
	return (get_page_nextpage(page));
}

void	*get_prev_page(void *page)
{
	return (get_page_prevpage(page));
}

void	dump_page(size_t *page)
{
	if (page == NULL || header_from_page(page) == NULL)
		return ;
	printf("page:\n%p,", page);
	printf("s:%zu,", get_page_size(page));
	printf("a:%zu,", get_page_allocations(page));
	printf("np:%p,", get_page_nextpage(page));
	printf("pp:%p,", get_page_prevpage(page));
}

void	*page_manager(t_ptype type)
{
	switch (type)
	{
		case TINY:
			return (g_heap->tiny);
		case MEDIUM:
			return (g_heap->medium);
		case LARGE:
			return (g_heap->large);
	}
}

/*

freepage()

*/
