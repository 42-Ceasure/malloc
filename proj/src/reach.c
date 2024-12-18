/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reach.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:48:49 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/18 09:49:17 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mymalloc.h"

void	*search_chunk_in_page(void *ptr, void *usr_ptr)
{
	while (get_chunk_size(ptr))
	{
		if (ptr == chkptr_from_usrptr(usr_ptr))
			return (ptr);
		ptr = next_chunk(ptr);
	}
	return (NULL);
}

void	*get_basic_chunk(void *page, void *usr_ptr)
{
	void	*ptr;

	while (page)
	{
		ptr = search_chunk_in_page(page, usr_ptr);
		if (ptr != NULL)
			return (page);
		page = get_next_page(page);
	}
	return (NULL);
}

void	*get_user_page(void *usr_ptr)
{
	void	*page;

	page = get_basic_chunk(heap_manager(TINY), usr_ptr);
	if (page != NULL)
		return (page);
	page = get_basic_chunk(heap_manager(MEDIUM), usr_ptr);
	if (page != NULL)
		return (page);
	page = get_basic_chunk(heap_manager(LARGE), usr_ptr);
	if (page != NULL)
		return (page);
	return (NULL);
}
