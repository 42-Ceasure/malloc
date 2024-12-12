/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/12 13:03:15 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

size_t	aligned_size(const size_t user_size)
{
	size_t	padding;

	padding = (ALIGNMENT - (user_size % ALIGNMENT));
	if (padding == ALIGNMENT)
		padding = 0;
	return (user_size + padding + DATA_SIZE);
}

void	allocate(void *const ptr, const size_t size)
{
	if (get_chunk_size(ptr) != size)
		split_chunk(ptr, size);
	set_chunk(ptr, size, CHUNK_USED);
	set_wormhole(prev_free_chunk(ptr), next_free_chunk(ptr));
}

void	*memory_manager(size_t size)
{
	t_ptype type;
	void	*ptr;

	if (size <= TINY_SIZE)
		type = TINY;
	else if (size <= MEDIUM_SIZE)
		type = MEDIUM;
	else
		type = LARGE;
	ptr = find_ffit_chunk(page_manager(type), size);
	return (ptr);
}

void	*mymalloc(size_t user_size)
{
	void	*ptr = NULL;
	size_t	size;

	if (user_size < 1)
		return (NULL);
	if (g_heap == NULL)
		init_heap();
	size = aligned_size(user_size);
	if (DEBUG)
		printf("trying to allocate %zu bytes,", size);
	ptr = memory_manager(size);
	// ptr = find_ffit_chunk(g_heap->tiny, size);
	if (ptr == NULL)
	{
		if (DEBUG)
			printf(" NO SPACE FOUND.\n");
		return (NULL);
	}
	if (DEBUG)
		printf(" space found at %p\n", ptr);
	allocate(ptr, size);
	return (usrptr_from_chkptr(ptr));
}
