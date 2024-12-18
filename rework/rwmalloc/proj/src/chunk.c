/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:57:34 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/18 10:59:47 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

size_t	get_chunk_status(const void *const ptr)
{
	return (get_micro_data(ptr) & LSB);
}

size_t	get_chunk_size(const void *const ptr)
{
	return (get_micro_data(ptr) & NBR);
}

void	*chkptr_from_usrptr(void *ptr)
{
	return (ptr - HEAD_SIZE);
}

void	*usrptr_from_chkptr(void *ptr)
{
	return (ptr + HEAD_SIZE);
}

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

void	*find_lfit_chunk(void *heap, const size_t size)
{
	void	*ptr;

	ptr = heap;
	while (ptr)
	{
		if (!get_chunk_status(ptr) && get_chunk_size(ptr) >= size)
			return (ptr);
		ptr = jump_prev_free_chunk(heap, ptr);
	}
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

void	*jump_next_free_chunk(void *ptr)
{
	if (get_chunk_status(ptr))
		ptr = next_free_chunk(ptr);
	else
	{
		if (!get_chunk_size(ptr + HEAD_SIZE))
			return (NULL);
		ptr = ptr + get_chunk_size(ptr + HEAD_SIZE);
	}
	return (ptr);
}

void	*next_free_chunk(void *ptr)
{
	do
		ptr = next_chunk(ptr);
	while (ptr && (get_chunk_status(ptr) || get_chunk_size(ptr) == DATA_SIZE)); 
	return (ptr);
}

void	*next_chunk(void *ptr)
{
	if (!get_chunk_size(ptr))
		return (NULL);
	ptr = ptr + get_chunk_size(ptr);
	return (ptr);
}

void	set_head_ptr(void *const ptr, const size_t size)
{
	set_micro_data(ptr + HEAD_SIZE, size);
}

void	set_foot_ptr(void *const ptr,  size_t size)
{
	size_t	shift;

	shift = get_chunk_size(ptr);
	if (shift == 0)
		shift = END_CHUNK;
	set_micro_data((ptr + shift - FOOT_SIZE - FOOT_SIZE), size);
}

void	set_wormhole(void *const ptr1, void *const ptr2)
{
	size_t	size;

	if (ptr2 == NULL)
		return ;
	if (ptr1 == NULL)
	{
		set_foot_ptr(ptr2, 0);
		return ;
	}
	if (ptr1 == ptr2)
		size = (get_chunk_size(ptr1));
	else
		size = ptr2 - ptr1;
	set_head_ptr(ptr1, size);
	set_foot_ptr(ptr2, size);
}
