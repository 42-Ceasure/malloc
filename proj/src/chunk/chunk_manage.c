/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/11/26 11:44:28 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

void	*get_user_chunk(void *usr_ptr)
{
	void	*ptr;

	ptr = g_heap->tiny;
	while (get_chunk_size(ptr))
	{
		if (ptr == chkptr_from_usrptr(usr_ptr))
			return (ptr);
		ptr = next_chunk(ptr);
	}
	return (NULL);
}

void	*merge_chunks(void *const ptr1, void *const ptr2, const size_t status)
{
	set_chunk(ptr1, (get_chunk_size(ptr1) + get_chunk_size(ptr2)), status);
	return (ptr1);
}

void	split_chunk(void *const ptr, const size_t size)
{
	size_t	new_size;

	new_size = get_chunk_size(ptr) - size;
	set_chunk(ptr + size, new_size, CHUNK_FREE);
	if (!get_chunk_status(next_chunk(ptr + size)))
		merge_chunks(ptr + size, next_chunk(ptr + size), CHUNK_FREE);
	if (new_size > DATA_SIZE)
		set_wormhole(ptr + size, next_free_chunk(ptr));
}
