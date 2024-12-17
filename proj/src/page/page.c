/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/17 16:15:41 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <page.h>

void	*getmap(const size_t len)
{
	void	*map;

	map = mmap(	NULL,
				len,
				PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS,
				-1,
				0);
	return (map);
}

void	set_page_size(size_t *page, size_t size)
{
	*(page + SIZE) = size;
}
void	set_page_allocations(size_t *page, size_t allocations)
{
	*(page + ALLOC) = allocations;
}
void	inc_page_allocations(size_t *page)
{
	set_page_allocations(page, get_page_allocations(page) + 1);
}
void	dec_page_allocation(size_t *page)
{
	set_page_allocations(page, get_page_allocations(page) - 1);
}
void	set_page_nextpage(size_t *page, size_t *nextpage)
{
	write_adress((page + NEXTP), nextpage);
}
void	set_page_prevpage(size_t *page, size_t *prevpage)
{
	write_adress((page + PREVP), prevpage);
}
void	set_page_to_init(void *page)
{
	write_adress(page, NULL);
}

size_t	get_page_size(size_t *page)
{
	return (*(page + SIZE));
}
size_t	get_page_usable_size(size_t *page)
{
	return (*(page + SIZE) - PAGE_HEADSIZE);
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
size_t	is_page_inited(void *page)
{
	if (get_adress(page) != NULL)
		return (1);
	return (0);
}

void	init_page_header(void *page, size_t size)
{
	set_page_size(page, size);
	set_page_allocations(page, 0);
	set_page_nextpage(page, NULL);
	set_page_prevpage(page, NULL);
	set_page_to_init(page);
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

void	*extend_page(void *page)
{
	void	*end;
	void	*new;

	new = new_page(get_page_size(page) / PAGE_SIZE);
	end = page;
	while (get_next_page(end))
		end = get_next_page(end);
	link_pages(end, new);
	return (new);
}

void	*new_page(size_t nb)
{
	void	*page;
	size_t	size;

	size = nb * PAGE_SIZE;
	page = page_from_header(getmap(size));
	init_page_header(page, size);
	return (page);
}

void	*new_specific_page(size_t size)
{
	size_t	nb = 0;

	while ((nb * PAGE_SIZE) < size)
		nb++;
	return (getmap(nb));
}

void	*get_next_page(void *page)
{
	return (get_page_nextpage(page));
}

void	*get_prev_page(void *page)
{
	return (get_page_prevpage(page));
}

void	*page_manager(void *page)
{
	void	*next;

	next = get_next_page(page);
	if (next == NULL)
	{
		page = extend_page(page);
		if (page == NULL)
			return (NULL);
	}
	else
		page = next;
	return (page);
}

/*

freepage()

*/
