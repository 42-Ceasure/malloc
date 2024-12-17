/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/17 15:48:37 by cglavieu         ###   ########.fr       */
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

void	allocate(void *page, void *const ptr, const size_t size)
{
	if (get_chunk_size(ptr) != size)
		split_chunk(ptr, size);
	set_chunk(ptr, size, CHUNK_USED);
	set_wormhole(prev_free_chunk(page, ptr), next_free_chunk(ptr));
	inc_page_allocations(page);
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

void	*large_alloc(void *heap, size_t size)
{
	void	*usr_ptr;
	void	*ptr;

	usr_ptr = new_specific_page(size);
	if (usr_ptr == NULL)
		return (NULL);
	ptr = chunk_manager(&heap, 32); /* la je vais devoir creer un tracking
	de mes maps, je pense utiliser la page heap large avec une version plus
	light de chunk_manager, pour garder la "taille" et le pointeur vers la
	zone memoire. 16 = header + ptr, pas de footer, a reflechir.
	*/
	allocate(heap, ptr, 32);
	write_adress(ptr + HEAD_SIZE, usr_ptr);
	set_micro_data(ptr + DATA_SIZE, size);
	return (usr_ptr);
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
		ptr = chunk_manager(&heap, size);
	else
	{
		printf(" space found at %p\n", ptr);
		return (large_alloc(heap, user_size));
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
