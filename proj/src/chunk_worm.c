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
