/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/11 12:48:24 by cglavieu         ###   ########.fr       */
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
	*(page + SIZE) = size;
}
void	set_page_type(size_t *page, size_t type)
{
	*(page + TYPE) = type;
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
void	set_page_freespace(size_t *page, size_t freespace)
{
	*(page + FSPACE) = freespace;
}
void	set_page_largestfreespace(size_t *page, size_t largestfreespace)
{
	*(page + LFSPACE) = largestfreespace;
}
void	set_page_smallestfreespace(size_t *page, size_t smallestfreespace)
{
	*(page + SFSPACE) = smallestfreespace;
}

size_t	get_page_size(size_t *page)
{
	return (*(page + SIZE));
}
size_t	get_page_type(size_t *page)
{
	return (*(page + TYPE));
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
size_t	get_page_freespace(size_t *page)
{
	return (*(page + FSPACE));
}
size_t	get_page_largestfreespace(size_t *page)
{
	return (*(page + LFSPACE));
}
size_t	get_page_smallestfreespace(size_t *page)
{
	return (*(page + SFSPACE));
}

void	init_page(void *page, size_t size)
{
	set_page_size(page, size);
	set_page_type(page, 0);
	set_page_allocations(page, 0);
	set_page_nextpage(page, NULL);
	set_page_prevpage(page, NULL);
	set_page_freespace(page, size - PAGE_HEADSIZE);
	set_page_largestfreespace(page, size - PAGE_HEADSIZE);
	set_page_smallestfreespace(page, size - PAGE_HEADSIZE);
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
	printf("page:%p,", header_from_page(page));
	printf("s:%zu,", get_page_size(page));
	printf("t:%zu,", get_page_type(page));
	printf("a:%zu,", get_page_allocations(page));
	printf("np:%p,", get_page_nextpage(page));
	printf("pp:%p,", get_page_prevpage(page));
	printf("fs:%zu,", get_page_freespace(page));
	printf("lfs:%zu,", get_page_largestfreespace(page));
	printf("sfs:%zu\n", get_page_smallestfreespace(page));
}

/*

freepage()

*/
