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

size_t	set_chunk_size(const size_t size)
{
	size_t	padding;

	padding = (ALIGNMENT - (size % ALIGNMENT));
	if (padding == ALIGNMENT)
		padding = 0;
	return (size + padding + DATA_SIZE);
}

void	*mymalloc(size_t usr_size)
{
	void	*ptr;
	size_t	chunk_size;

	if (usr_size < 1 || usr_size > USR_USABLE)
		return (NULL);
	ptr = heap; // this will be soon given by the system.
	// I will also need to do something similar to "init heap on that memory"
	chunk_size = set_chunk_size(usr_size);
	ptr = find_ffit_chunk(ptr, chunk_size);
	if (ptr == NULL)
		return (NULL);
	if (get_chunk_size(ptr) != chunk_size)
		split_chunk(ptr, chunk_size);
	set_chunk(ptr, chunk_size, CHUNK_USED);
	return (usrptr_from_chunk(ptr));
}
