/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cpy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/10/25 10:55:12 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

void	*get_user_chunk(void *usr_ptr)
{
	void	*ptr;

	ptr = heap;
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
	if (new_size > DATA_SIZE)
		set_wormhole(ptr + size, next_free_chunk(ptr));
}
