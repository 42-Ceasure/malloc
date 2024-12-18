/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/18 09:48:45 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

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
	if (!get_chunk_status(next_chunk(ptr + size)))
		merge_chunks(ptr + size, next_chunk(ptr + size), CHUNK_FREE);
	if (new_size > DATA_SIZE)
		set_wormhole(ptr + size, next_free_chunk(ptr));
}

void	*chunk_manager(void **page, size_t size)
{
	void	*ptr = NULL;

	while (page)
	{
		ptr = find_ffit_chunk(*page, size);
		if (ptr != NULL)
		{
			
			return (ptr);
		}
		else
		{
			*page = page_manager(*page);
			if (!is_page_inited(*page))
				init_page_chunks(*page, get_page_usable_size(*page));
		}
	}
	return (NULL);
}
