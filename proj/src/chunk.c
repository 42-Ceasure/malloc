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

size_t	get_chunk_size(size_t *ptr)
{
	return (*ptr & NBR);
}

int		is_chunk_free(size_t *ptr)
{
	return (*ptr & LSB);
}

void	set_header(size_t *ptr, size_t size, size_t used)
{
	*ptr = size + used;
}

void	set_footer(char *ptr, size_t size, size_t used)
{
	set_header((size_t *)(ptr + size - FOOT_SIZE), size, used);
}

void	*create_block(size_t *ptr, size_t size, size_t used)
{
	set_header(ptr, size, used);
	set_footer((char *)ptr, size, used);
	return (ptr + 1);
}

void	split_chunk(size_t *ptr, size_t size)
{
	char	*byte_ptr;
	size_t	chunk_size;

	chunk_size = *ptr - size;
	byte_ptr = (char *)ptr + size;
	create_block((size_t *)byte_ptr, chunk_size, CHUNK_FREE);
}
