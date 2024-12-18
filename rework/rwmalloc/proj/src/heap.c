/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:00:00 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/18 10:59:52 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

t_heap *g_heap = NULL;

void	init_tiny(void)
{
	g_heap->tiny = new_page(DEFAULT_TINY);
	init_page_chunks(g_heap->tiny, get_page_usable_size(g_heap->tiny));
}

void	init_medium(void)
{
	g_heap->medium = new_page(DEFAULT_MEDIUM);
	init_page_chunks(g_heap->medium, get_page_usable_size(g_heap->medium));
}

void	init_large(void)
{
	g_heap->large = new_page(DEFAULT_LARGE);
	init_page_chunks(g_heap->large, get_page_usable_size(g_heap->large));
}

void	init_heap(void)
{
	static	t_heap heap;

	g_heap = &heap;
	g_heap->tiny = NULL;
	g_heap->medium = NULL;
	g_heap->large = NULL;
}

void	*heap_manager(t_atype type)
{
	if (g_heap == NULL)
		init_heap();
	switch (type)
	{
		case TINY:
			if (g_heap->tiny == NULL)
				init_tiny();
			return (g_heap->tiny);
		case MEDIUM:
			if (g_heap->medium == NULL)
				init_medium();
			return (g_heap->medium);
		case LARGE:
			if (g_heap->large == NULL)
				init_large();
			return (g_heap->large);
	}
}