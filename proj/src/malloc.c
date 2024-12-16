/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/16 11:48:59 by cglavieu         ###   ########.fr       */
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

size_t	check_user_size(const size_t user_size)
{
	if (user_size < 1)
		return (0);
	return (aligned_size(user_size));
}

void	allocate(void *heap, void *const ptr, const size_t size)
{
	if (get_chunk_size(ptr) != size)
		split_chunk(ptr, size);
	set_chunk(ptr, size, CHUNK_USED);
	set_wormhole(prev_free_chunk(heap, ptr), next_free_chunk(ptr));
}

t_atype	type_manager(size_t size)
{
	t_atype type;

	if (size <= TINY_SIZE)
		type = TINY;
	else if (size <= MEDIUM_SIZE)
		type = MEDIUM;
	else
		type = LARGE;
	return (type);
}

void	*mymalloc(size_t user_size)
{
	void	*ptr = NULL;
	void	*heap;
	size_t	size;
	t_atype	type;

	size = check_user_size(user_size);
	if (size == 0)
		return (NULL);
	if (DEBUG)
		printf("trying to allocate %zu bytes,", size);
	type = type_manager(size);
	heap = heap_manager(type);
	if (type != LARGE)
		ptr = chunk_manager(heap, size);
	else
	{
		// big alloc;
		return (NULL);
	}
	if (ptr == NULL)
	{
		if (DEBUG)
			printf(" NO SPACE FOUND.\n");
		return (NULL);
	}
	if (DEBUG)
		printf(" space found at %p\n", ptr);
	allocate(heap, ptr, size);
	return (usrptr_from_chkptr(ptr));
}
