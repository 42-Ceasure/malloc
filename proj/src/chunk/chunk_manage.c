/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/16 11:48:43 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

void	*search_chunk_in_page(void *ptr, void *usr_ptr)
{
	while (get_chunk_size(ptr))
	{
		if (ptr == chkptr_from_usrptr(usr_ptr))
			return (ptr);
		ptr = next_chunk(ptr);
	}
	return (NULL);
}

void	*get_user_chunk_in(void *page, void *usr_ptr)
{
	void	*ptr;

	while (page)
	{
		ptr = search_chunk_in_page(page, usr_ptr);
		if (ptr != NULL)
			return (ptr);
		page = get_next_page(page);
	}
	return (NULL);
}

void	*get_user_chunk(void *usr_ptr)
{
	void	*ptr;

	ptr = get_user_chunk_in(heap_manager(TINY), usr_ptr);
	if (ptr != NULL)
		return (heap_manager(TINY));
	ptr = get_user_chunk_in(heap_manager(MEDIUM), usr_ptr);
	if (ptr != NULL)
		return (heap_manager(MEDIUM));
	ptr = get_user_chunk_in(heap_manager(LARGE), usr_ptr);
	if (ptr != NULL)
		return (heap_manager(LARGE));
	return (NULL);
}

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

void	*chunk_manager(void *page, size_t size)
{
	void	*ptr = NULL;

	while (page)
	{
		ptr = find_ffit_chunk(page, size);
		if (ptr != NULL)
			return (ptr);
		else
		{
			page = page_manager(page);
			if (!is_page_inited(page))
				init_page_chunks(page, get_page_usable_size(page));
		}
	}
	return (NULL);
}
