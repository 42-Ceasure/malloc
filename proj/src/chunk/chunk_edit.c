/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/13 16:39:36 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

void	set_header(void *const ptr, const size_t size, const size_t status)
{
	set_micro_data(ptr, size + status);
}

void	set_footer(void *const ptr, const size_t size, const size_t status)
{
	set_micro_data(ptr + size - FOOT_SIZE, size + status);
}

void	set_chunk(void *const ptr, const size_t size, const size_t status)
{
	set_header(ptr, size, status);
	set_footer(ptr, size, status);
}

void	init_page_chunks(void *ptr, size_t size)
{
	size = size - END_CHUNK;
	set_chunk(ptr, size, CHUNK_FREE);
	set_header(ptr + size, 0, CHUNK_FREE);
	set_footer(ptr + size + END_CHUNK, 0, CHUNK_FREE);
	set_wormhole(ptr, ptr + size);
}
