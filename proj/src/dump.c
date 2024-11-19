/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/11/18 11:12:19 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

void	dump_chunk_datas(void *ptr)
{
	size_t	size;
	size_t	*byte;

	size = get_chunk_size(ptr);
	if (size == 0)
		size = 32;
	byte = ptr;
	while ((void *)byte < ptr + DATA_SIZE)
		printf("%zu,", *byte++);
	byte = ptr + size - DATA_SIZE;
	while ((void *)byte < ptr + size)
		printf("%zu,", *byte++);
	printf("\n");
}

void	dump_chunk(void *ptr)
{
	if (ptr)
	{
		printf("chunkptr:%p,", ptr);
		if (is_chunk_used(ptr))
			printf("usrptr:%p,", usrptr_from_chkptr(ptr));
		printf("status:%s,", is_chunk_used(ptr) == 1 ? "USED" : "FREE");
		printf("size:%zu\n", get_chunk_size(ptr));
		if (!is_chunk_used(ptr))
			dump_chunk_datas(ptr);
	}
}

void	dump_heap(void)
{
	void	*ptr;

	ptr = heap; // as for mymalloc, this will be soon given by the system.
	// I will need to think passing area to that function
	printf("------------------------\n");
	printf("heap state :\n");
	printf("------------------------\n");
	while (get_chunk_size(ptr))
	{
		dump_chunk(ptr);
		ptr = next_chunk(ptr);
	}
	printf("------------------------\n");
}
