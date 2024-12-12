/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/12 06:48:44 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

static void	invalid_pointer(void)
{
	printf("myrealloc(): invalid pointer\n");
	exit(1);
}

void	*realloc_more_here(void *ptr, void *next, size_t size)
{
	merge_chunks(ptr, next, 0);
	allocate(ptr, size);
	return (usrptr_from_chkptr(ptr));
}

void	*realloc_more_elsewhere(void *old, size_t size)
{
	size_t	usr_data_size;
	void	*new;

	new = mymalloc(size);
	if (new == NULL)
		return (NULL);
	usr_data_size = get_chunk_size(old) - DATA_SIZE;
	memcpy(new, usrptr_from_chkptr(old), usr_data_size);
	deallocate(old);
	return (new);
}

void	*reallocate(void *chk_ptr, size_t usr_size)
{
	size_t	size;
	void	*next;

	if (chk_ptr == NULL)
		invalid_pointer();
	size = aligned_size(usr_size);
	if (size < get_chunk_size(chk_ptr))
		allocate(chk_ptr, size);
	else
	{
		next = next_chunk(chk_ptr);
		if (!get_chunk_status(next))
			if (size <= get_chunk_size(chk_ptr) + get_chunk_size(next))
				return (realloc_more_here(chk_ptr, next, size));
		return (realloc_more_elsewhere(chk_ptr, usr_size));
	}
	return (usrptr_from_chkptr(chk_ptr));
}

void	*myrealloc(void *ptr, size_t usr_size)
{
	if (ptr == NULL)
		return (mymalloc(usr_size));
	else if (usr_size == 0)
		myfree(ptr);
	else if (usr_size == aligned_size(usr_size))
		return (ptr);
	else
		return (reallocate(get_user_chunk(ptr), usr_size));
	return (NULL);
}
