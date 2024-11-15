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

void	*realloc(void *ptr, size_t usr_size)
{
	void	*tmp;
	void	*chunk_ptr;
	size_t	usr_data_size;
	size_t	usr_chunk_size;	
	size_t	size;

	if (ptr == NULL)
		return (mymalloc(usr_size));
	else if (size == 0)
		myfree(ptr);
	chunk_ptr = get_user_chunk(ptr);
	if (chunk_ptr == NULL)
		return (NULL); // invalid pointer
	size = set_chunk_size(usr_size);
	usr_chunk_size = get_chunk_size(chunk_ptr);
	usr_data_size = usr_chunk_size - DATA_SIZE;
	if (size < usr_chunk_size)
		allocate(chunk_ptr, size);
	else if (size > usr_chunk_size)
	{
		tmp = next_chunk(chunk_ptr);
		if (!is_chunk_used(tmp) && size < usr_chunk_size + get_chunk_size(tmp))
		{
			merge_chunks(chunk_ptr, tmp, 0);
			allocate(chunk_ptr, size);
			return (ptr);
		}
		else
		{
			tmp = mymalloc(usr_size);
			memcpy(usrptr_from_chkptr(tmp), ptr, usr_data_size);
			myfree(ptr);
			return (tmp);
		}
	}
	return (NULL);
}
