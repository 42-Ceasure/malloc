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

size_t	calc_blockSize(size_t size)
{
	size_t	padding;

	padding = (ALIGNMENT - (size % ALIGNMENT));
	if (padding == ALIGNMENT)
		padding = 0;
	size = size + padding + HEAD_SIZE + FOOT_SIZE;
	return (size);
}

void	*mymalloc(size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (size < 1 || size > MAX_USABLE)
		return (ptr);
	size = calc_blockSize(size);
	ptr = find_ffit_chunk(ptr, size);
	if (ptr == NULL)
		return (ptr);
	split_chunk(ptr, size);
	ptr = create_block(ptr, size, CHUNK_USED);
	return (ptr);
}
