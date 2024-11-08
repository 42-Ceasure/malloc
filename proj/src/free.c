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

void	myfree(void *user_ptr)
{
	void	*tmp;

	if (user_ptr == NULL || (size_t)user_ptr % 8 != 0)
		return ;
	user_ptr = chunk_from_usrptr(user_ptr);
	if (user_ptr < (void *)heap || user_ptr > (void *)heap + USR_USABLE)
		return ;
	set_chunk(user_ptr, get_chunk_size(user_ptr), CHUNK_FREE);
	tmp = next_chunk(user_ptr);
	if (tmp && !is_chunk_free(tmp))
		merge_chunks(user_ptr, tmp, CHUNK_FREE);
	tmp = prev_chunk(user_ptr);
	if (tmp && !is_chunk_free(tmp))
		merge_chunks(tmp, user_ptr, CHUNK_FREE);
}
