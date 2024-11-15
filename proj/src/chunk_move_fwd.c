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

void	*jump_next_free_chunk(void *ptr)
{
	if (is_chunk_used(ptr))
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
	while (ptr && (is_chunk_used(ptr) || get_chunk_size(ptr) == DATA_SIZE)); 
	return (ptr);
}

void	*next_chunk(void *ptr)
{
	if (!get_chunk_size(ptr))
		return (NULL);
	ptr = ptr + get_chunk_size(ptr);
	return (ptr);
}
