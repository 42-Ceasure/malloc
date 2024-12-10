/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/10 16:31:56 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

void			*getmap(const size_t len)
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

t_page_header	get_page_header(size_t *page)
{
	t_page_header dst;

	dst.size = get_page_size(page);
	dst.type = get_page_type(page);
	dst.allocations = get_page_allocations(page);
	dst.nextpage = get_page_nextpage(page);
	dst.prevpage = get_page_prevpage(page);
	dst.freespace = get_page_freespace(page);
	dst.largestfreespace = get_page_largestfreespace(page);
	dst.smallestfreespace = get_page_smallestfreespace(page);
	return (dst);
}

void			set_page_header(size_t *page, t_page_header src)
{
	set_page_size(page, src.size);
	set_page_type(page, src.type);
	set_page_allocations(page, src.allocations);
	set_page_nextpage(page, src.nextpage);
	set_page_prevpage(page, src.prevpage);
	set_page_freespace(page, src.freespace);
	set_page_largestfreespace(page, src.largestfreespace);
	set_page_smallestfreespace(page, src.smallestfreespace);
}

void			*nextpage(size_t *page)
{
	return (get_page_nextpage(page));
}

void			*prevpage(size_t *page)
{
	return (get_page_prevpage(page));
}

void	init_page(void *page, size_t size)
{
	t_page_header	base;

	base.size = size;
	base.type = 0;
	base.allocations = 0;
	base.nextpage = NULL;
	base.prevpage = NULL;
	base.freespace = size - PAGE_HEADSIZE;
	base.largestfreespace = base.freespace;
	base.smallestfreespace = base.freespace;
	set_page_header(page, base);
}

void	*get_page(size_t nb)
{
	void	*page;
	size_t	size;

	size = nb * PAGE_SIZE;
	page = getmap(size);
	init_page(page, size);
	return (page);
}

void			*getXpages(const size_t x)
{
	return (getmap(x * PAGE_SIZE));
}

void	dump_page(size_t *ptr)
{
	size_t	i;

	i = 0;
	while (i < 8)
	{
		printf("%zu,", ptr[i]);
		i++;
	}
	printf("\n");
}

/*

freepage()

linkpages()

*/
