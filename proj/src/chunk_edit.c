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

void	set_header(size_t *ptr, const size_t size, const size_t used)
{
	*ptr = size + used;
}

void	set_footer(void *ptr, const size_t size, const size_t used)
{
	set_header(ptr + size - FOOT_SIZE, size, used);
}

void	set_chunk(void *ptr, const size_t size, const size_t used)
{
	set_header(ptr, size, used);
	set_footer(ptr, size, used);
}

void	merge_chunks(void *ptr1, void *ptr2, const size_t used)
{
	set_chunk(ptr1, (get_chunk_size(ptr1) + get_chunk_size(ptr2)), used);
}

void	split_chunk(void *ptr, const size_t size)
{
	set_chunk(ptr + size, (get_chunk_size(ptr) - size), CHUNK_FREE);
}