/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:03:32 by cglavieu          #+#    #+#             */
/*   Updated: 2025/02/13 14:07:22 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define PAGE_SIZE		(getpagesize())
# define PAGE_ELEMENTS	(8)
# define PAGE_HEADSIZE	(PAGE_ELEMENTS * sizeof(size_t))

# define DEFAULT_TINY	(2)
# define DEFAULT_MEDIUM	(8)
# define DEFAULT_LARGE	(1)

# define ID				0
# define NEXTPAGE		1
# define PREVPAGE		2
# define LASTPAGE		3
# define ALLOCATIONS	4
# define MAXALLOCABLE	5
# define STARTADDR		6
# define STOPADDR		7
# define START			8


typedef	struct	s_heap
{
	void	*tiny;
	void	*medium;
	void	*large;
}				t_heap;

t_heap *g_heap = NULL;

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

void	init_heap(void)
{
	static	t_heap heap;

	g_heap = &heap;
	g_heap->tiny = NULL;
	g_heap->medium = NULL;
	g_heap->large = NULL;
}

void	set_page_id(size_t *page, size_t id)
{
	*(page + ID) = id;
}
void	set_page_nxtp(size_t *page, size_t *nextpage)
{
	write_adress((page + NEXTPAGE), nextpage);
}
void	set_page_prvp(size_t *page, size_t *prevpage)
{
	write_adress((page + PREVPAGE), prevpage);
}
void	set_page_endp(size_t *page, size_t *lastpage)
{
	write_adress((page + LASTPAGE), lastpage);
}
void	set_page_alloc(size_t *page, size_t allocations)
{
	*(page + ALLOCATIONS) = allocations;
}
void	set_page_max(size_t *page, size_t maxallocable)
{
	*(page + MAXALLOCABLE) = maxallocable;
}
void	set_page_start(size_t *page, size_t *startaddr)
{
	write_adress((page + STARTADDR), startaddr);
}
void	set_page_stop(size_t *page, size_t *stopaddr)
{
	write_adress((page + STOPADDR), stopaddr);
}

size_t	get_page_id(size_t *page, size_t id)
{
	return (*(page + ID));
}
void	*get_page_nxtp(size_t *page, size_t *nextpage)
{
	return (get_adress(page + NEXTPAGE));
}
void	*get_page_prvp(size_t *page, size_t *prevpage)
{
	return (get_adress(page + NEXTPAGE));
}
void	*get_page_endp(size_t *page, size_t *lastpage)
{
	return (get_adress(page + LASTPAGE));
}
size_t	get_page_alloc(size_t *page, size_t allocations)
{
	return (*(page + ALLOCATIONS));
}
size_t	get_page_max(size_t *page, size_t maxallocable)
{
	return (*(page + MAXALLOCABLE));
}
void	*get_page_start(size_t *page, size_t *startaddr)
{
	return (get_adress(page + STARTADDR));
}
void	*get_page_stop(size_t *page, size_t *stopaddr)
{
	return (get_adress(page + STOPADDR));
}

void	init_page_header(void *page, size_t size)
{
	static size_t	id = 0;

	set_page_id(size_t *page, id);
	set_page_nxtp(size_t *page, NULL);
	set_page_prvp(size_t *page, NULL);
	set_page_endp(size_t *page, NULL);
	set_page_alloc(size_t *page, 0);
	set_page_max(size_t *page, size - PAGE_HEADSIZE);
	set_page_start(size_t *page, page + START);
	set_page_stop(size_t *page, page + size);
	id++;
}

void	*new_page(size_t nb)
{
	void	*page;
	size_t	size;

	size = nb * PAGE_SIZE;
	page = getmap(size);
	init_page_header(page, size);
	return (page);
}

int		is_type_inited(t_type type)
{
	if (g_heap == NULL)
	{
		init_heap();
		return (0);
	}
	switch (type)
	{
		case TINY:
			if (g_heap->tiny == NULL)
				return (0);
		case MEDIUM:
			if (g_heap->medium == NULL)
				return (0);
		case LARGE:
			if (g_heap->large == NULL)
				return (0);
	}
	return (1);
}

void	set_type_root(t_type type)
{
	switch (type)
	{
		case TINY:
			g_heap->tiny = new_page(DEFAULT_TINY);
		case MEDIUM:
			g_heap->medium = new_page(DEFAULT_MEDIUM);
		case LARGE:
			g_heap->large = new_page(DEFAULT_LARGE);
	}
}

void	*get_type_root(t_type type)
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
		
void	*find_fit_page(void *page, size_t size);

void	extend_root(void *page);
