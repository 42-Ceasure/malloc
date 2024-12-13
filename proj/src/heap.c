/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/13 16:56:23 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <heap.h>

t_heap *g_heap = NULL;

void	init_tiny(void)
{
	g_heap->tiny = new_page(DEFAULT_TINY);
}

void	init_medium(void)
{
	g_heap->medium = new_page(DEFAULT_MEDIUM);
}

void	init_large(void)
{
	g_heap->large = new_page(DEFAULT_LARGE);
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