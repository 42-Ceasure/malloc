/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/16 11:40:29 by cglavieu         ###   ########.fr       */
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

void	deallocate(void *start, void *ptr)
{
	set_chunk(ptr, get_chunk_size(ptr), CHUNK_FREE);
	if (get_chunk_size(next_chunk(ptr))
		&& (!get_chunk_status(next_chunk(ptr))))
		merge_chunks(ptr, next_chunk(ptr), CHUNK_FREE);
	if (prev_chunk(start, ptr) && (!get_chunk_status(prev_chunk(start, ptr))))
		ptr = merge_chunks(prev_chunk(start, ptr), ptr, CHUNK_FREE);
	set_wormhole(ptr, next_free_chunk(ptr));
	set_wormhole(prev_free_chunk(start, ptr), ptr);
}

void	myfree(void *usr_ptr)
{
	void	*start;
	void	*ptr = NULL;

	if ((usr_ptr != NULL))
	{
		start = get_user_chunk(usr_ptr);
		if (start == NULL)
			invalid_pointer();
		else
			ptr = chkptr_from_usrptr(usr_ptr);
		if (!get_chunk_status(ptr))
			double_free();
		if (DEBUG)
			printf("deallocating %p (%zu bytes)\n", ptr, get_chunk_size(ptr));
		deallocate(start, ptr);
	}
}
