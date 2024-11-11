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

void	*jump_prev_free_chunk(void *ptr)
{
	if (is_chunk_used(ptr) || get_chunk_size(ptr) == 0)
		ptr = prev_free_chunk(ptr);
	else
	{
		if (*(size_t *)(ptr + get_chunk_size(ptr) - (2 *FOOT_SIZE)) == 0)
			return (NULL);
		ptr = ptr - *(size_t *)(ptr + get_chunk_size(ptr) - (2 *FOOT_SIZE)); 
	}
	return (ptr);
}

void	*prev_free_chunk(void *ptr)
{
	do
	{
		ptr = prev_chunk(ptr);
		if (ptr ==  NULL)
			return (ptr);
	}
	while (is_chunk_used(ptr)); 
	return (ptr);
}

void	*prev_chunk(void *ptr)
{
	ptr = ptr - (*(size_t *)(ptr - FOOT_SIZE) & NBR);
	if (ptr < heap)
		return (NULL);
	return (ptr);
}
