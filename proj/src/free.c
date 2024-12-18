/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/18 09:04:23 by cglavieu         ###   ########.fr       */
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

void	deallocate(void *page, void *ptr)
{
	set_chunk(ptr, get_chunk_size(ptr), CHUNK_FREE);
	if (get_chunk_size(next_chunk(ptr))
		&& (!get_chunk_status(next_chunk(ptr))))
		merge_chunks(ptr, next_chunk(ptr), CHUNK_FREE);
	if (prev_chunk(page, ptr) && (!get_chunk_status(prev_chunk(page, ptr))))
		ptr = merge_chunks(prev_chunk(page, ptr), ptr, CHUNK_FREE);
	set_wormhole(ptr, next_free_chunk(ptr));
	set_wormhole(prev_free_chunk(page, ptr), ptr);
	dec_page_allocation(page);
}

void	myfree(void *usr_ptr)
{
	void	*page;
	void	*ptr = NULL;

	if ((usr_ptr != NULL))
	{
		page = get_user_page(usr_ptr);
		if (page == NULL)
			invalid_pointer();
		else
			ptr = chkptr_from_usrptr(usr_ptr);
		if (!get_chunk_status(ptr))
			double_free();
		if (DEBUG)
			printf("deallocating %p (%zu bytes)\n", ptr, get_chunk_size(ptr));
		deallocate(page, ptr);
	}
}
