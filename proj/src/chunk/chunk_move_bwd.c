/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_move_bwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/16 11:47:27 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

/* *************** to check - may not work anymore ************************** */
void	*jump_prev_free_chunk(void *heap, void *ptr)
{
	if (get_chunk_status(ptr) || get_chunk_size(ptr) == 0)
		ptr = prev_free_chunk(heap, ptr);
	else
	{
		if (*(size_t *)(ptr + get_chunk_size(ptr) - (2 *FOOT_SIZE)) == 0)
			return (NULL);
		ptr = ptr - *(size_t *)(ptr + get_chunk_size(ptr) - (2 *FOOT_SIZE)); 
	}
	return (ptr);
}
/* ************************************************************************** */

void	*prev_free_chunk(void *heap, void *ptr)
{
	do
		ptr = prev_chunk(heap, ptr);
	while (ptr && (get_chunk_status(ptr) || get_chunk_size(ptr) == DATA_SIZE));
	return (ptr);
}

void	*prev_chunk(void *heap, void *ptr)
{
	if (ptr <= heap)
		return (NULL);
	ptr = ptr - (*(size_t *)(ptr - FOOT_SIZE) & NBR);
	return (ptr);
}
