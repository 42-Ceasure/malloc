/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/23 07:28:02 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <page.h>

/*-- "private"  --*/
static void		*get_adress(size_t *adress)
{
	return ((void *)*adress);
}
static void		write_adress(size_t *where, size_t *adress)
{
	*where = (size_t)adress;
}

static void		*new_map(const size_t len)
{
	return (mmap(	NULL,
				len,
				PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS,
				-1,
				0)); // return ptr on success, (void *)-1 on error. set errno
}
static void		del_map(void *page, const size_t len)
{
	munmap(page, len); // ret 0 on success, -1 on error. set errno
}

static size_t	get_page_prevpage(size_t *page)
{
	return (*(page + PAGEPREV));
}
static void		set_page_prevpage(size_t *page, size_t *prevpage)
{
	write_adress(page + PAGEPREV, prevpage);
}
static size_t	get_page_nextpage(size_t *page)
{
	return (*(page + PAGENEXT));
}
static void		set_page_nextpage(size_t *page, size_t *nextpage)
{
	write_adress(page + PAGENEXT, nextpage);
}
static size_t	get_page_size(size_t *page)
{
	return (*(page + PAGESIZE));
}
static void		set_page_size(size_t *page, const size_t size)
{
	*(page + PAGESIZE) = size;
}
static size_t	get_page_type(size_t *page)
{
	return (*(page + PAGETYPE));
}
static void		set_page_type(size_t *page, const size_t type)
{
	*(page + PAGETYPE) = type;
}
static size_t	get_page_alloc(size_t *page)
{
	return (*(page + PAGEALLOC));
}
static void		set_page_alloc(size_t *page, const size_t alloc)
{
	*(page + PAGEALLOC) = alloc;
}

/*--- "public" ---*/
void			init_page(void *page, const size_t size, const size_t type)
{
	set_page_prevpage(page, NULL);
	set_page_nextpage(page, NULL);
	set_page_size(page, size);
	set_page_type(page, type);
	set_page_alloc(page, 0);
}
void			*new_page(const size_t nb)
{
	return (new_map(nb * SYS_PAGESIZE));
}
void			del_page(void *page)
{
	del_map(page, get_page_size(page));
}

size_t			get_page_info(void *page, t_epe element)
{
	switch (element)
	{
		case SIZE:
			return (get_page_size(page));
		case TYPE:
			return (get_page_type(page));
		case ALLOC:
			return (get_page_alloc(page));
		case PREV:
			return (get_page_prevpage(page));
		case NEXT:
			return (get_page_nextpage(page));
	}
}
void			*get_prev_page(void *page)
{
	return (get_adress(page + PAGEPREV));
}
void			*get_next_page(void *page)
{
	return (get_adress(page + PAGENEXT));
}

void			increment_page_alloc(void *page)
{
	set_page_alloc(page, (get_page_alloc(page) + 1));
}
void			decrement_page_alloc(void *page)
{
	set_page_alloc(page, (get_page_alloc(page) - 1));
}
void			link_pages(void *page1, void *page2)
{
	set_page_nextpage(page1, page2);
	set_page_prevpage(page2, page1);
}

void			dump_page(void *page)
{
	printf("page:%p, ", page);
	printf("prev:%p, ", (void *)get_page_info(page, PREV));
	printf("next:%p, ", (void *)get_page_info(page, NEXT));
	printf("size:%zu, ", get_page_info(page, SIZE));
	printf("type:%zu, ", get_page_info(page, TYPE));
	printf("alloc:%zu, ", get_page_info(page, ALLOC));
	printf("\n");
}
