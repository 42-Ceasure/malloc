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

void	set_header(size_t *ptr, const size_t size, const size_t status)
{
	*ptr = size + status;
}

void	set_footer(void *ptr, const size_t size, const size_t status)
{
	set_header(ptr + size - FOOT_SIZE, size, status);
}

void	set_chunk(void *ptr, const size_t size, const size_t status)
{
	set_header(ptr, size, status);
	set_footer(ptr, size, status);
}

void	*merge_chunks(void *ptr1, void *ptr2, const size_t status)
{
	set_chunk(ptr1, (get_chunk_size(ptr1) + get_chunk_size(ptr2)), status);
	return (ptr1);
}

void	split_chunk(void *ptr, const size_t size)
{
	set_chunk(ptr + size, (get_chunk_size(ptr) - size), CHUNK_FREE);
}

void	set_wormhole(void *ptr1, void *ptr2)
{
	void	*tmp;

	if (ptr1 == NULL || ptr2 == NULL)
		return ;
	set_header(usrptr_from_chunk(ptr1), (size_t)(ptr2 - ptr1), CHUNK_FREE);
	tmp = ptr2 + get_chunk_size(ptr2) - (2 * FOOT_SIZE);
	set_header(tmp, (size_t)(ptr2 - ptr1), CHUNK_FREE);
}

void	set_fast_speed(void *ptr)
{
	set_wormhole(ptr, next_free_chunk(ptr));
	set_wormhole(prev_free_chunk(ptr), ptr);
}
