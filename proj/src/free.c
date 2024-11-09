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

void	myfree(void *ptr)
{
	void	*tmp;

	if ((ptr == NULL) || ((size_t)ptr % 8 != 0))
		return ;
	ptr = chunk_from_usrptr(ptr);
	if ((ptr < heap) || (ptr > heap + USR_USABLE))
		return ;
	set_chunk(ptr, get_chunk_size(ptr), CHUNK_FREE);
	tmp = next_chunk(ptr);
	if ((tmp) && (!is_chunk_used(tmp)))
		merge_chunks(ptr, tmp, CHUNK_FREE);
	tmp = prev_chunk(ptr);
	if ((tmp) && (!is_chunk_used(tmp)))
		ptr = merge_chunks(tmp, ptr, CHUNK_FREE);
	set_fast_speed(ptr);
}
