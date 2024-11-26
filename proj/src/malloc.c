/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/11/26 14:27:02 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

size_t	set_chunk_size(const size_t user_size)
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

void	*mymalloc(size_t user_size)
{
	void	*ptr = NULL;
	size_t	size;

	if (user_size < 1)
		return (NULL);
	if (g_heap == NULL)
		init_heap();
	size = set_chunk_size(user_size);
	if (DEBUG)
		printf("trying to allocate %zu bytes,", size);
	ptr = find_ffit_chunk(g_heap->tiny, size);
	if (ptr == NULL)
	{
		printf(" NO SPACE FOUND.\n");
		return (NULL);
	}
	printf("space found at %p\n", ptr);
	allocate(ptr, size);
	return (usrptr_from_chkptr(ptr));
}
