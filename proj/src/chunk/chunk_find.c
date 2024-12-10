/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/11/26 11:43:54 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

void	*find_ffit_chunk(void *ptr, const size_t size)
{
	while (ptr)
	{
		if (!get_chunk_status(ptr) && get_chunk_size(ptr) >= size)
			return (ptr);
		ptr = jump_next_free_chunk(ptr);
	}
	return (NULL);
}

void	*find_lfit_chunk(void *ptr, const size_t size)
{
	while (ptr)
	{
		if (!get_chunk_status(ptr) && get_chunk_size(ptr) >= size)
			return (ptr);
		ptr = jump_prev_free_chunk(ptr);
	}
	return (NULL);
}