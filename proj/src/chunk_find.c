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

void	*find_ffit_chunk(void *ptr, const size_t size)
{
	ptr = heap;

	while (ptr)
	{
		if (!is_chunk_used(ptr) && get_chunk_size(ptr) >= size)
			return (ptr);
		ptr = jump_next_free_chunk(ptr);
	}
	return (NULL);
}

void	*find_lfit_chunk(void *ptr, const size_t size)
{
	ptr = heap + MAX_USABLE;

	while (ptr)
	{
		if (!is_chunk_used(ptr) && get_chunk_size(ptr) >= size)
			return (ptr);
		ptr = jump_prev_free_chunk(ptr);
	}
	return (NULL);
}
