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

static void	double_free(void)
{
	printf("free(): double free detected\n");
	exit(1);
}

static void	invalid_pointer(void)
{
	printf("myfree(): invalid pointer\n");
	exit(1);
}

void	deallocate(void *ptr)
{
	void	*tmp;

	set_chunk(ptr, get_chunk_size(ptr), CHUNK_FREE);
	tmp = next_chunk(ptr);
	if ((tmp) && (!is_chunk_used(tmp)))
		merge_chunks(ptr, tmp, CHUNK_FREE);
	tmp = prev_chunk(ptr);
	if ((tmp) && (!is_chunk_used(tmp)))
		ptr = merge_chunks(tmp, ptr, CHUNK_FREE);
	set_wormhole(ptr, next_free_chunk(ptr));
	set_wormhole(prev_free_chunk(ptr), ptr);
}

void	myfree(void *usr_ptr)
{
	void	*ptr;

	if ((usr_ptr != NULL))
	{
		ptr = get_user_chunk(usr_ptr);
		if (ptr == NULL)
			invalid_pointer();
		if (!is_chunk_used(ptr))
			double_free();
		deallocate(ptr);
	}
}
