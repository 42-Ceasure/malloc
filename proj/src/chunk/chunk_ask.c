/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_ask.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/11/18 11:12:29 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

size_t	is_chunk_used(const void *const ptr)
{
	return (get_micro_data(ptr) & LSB);
}

size_t	get_chunk_size(const void *const ptr)
{
	return (get_micro_data(ptr) & NBR);
}

void	*chkptr_from_usrptr(void *ptr)
{
	return (ptr - HEAD_SIZE);
}

void	*usrptr_from_chkptr(void *ptr)
{
	return (ptr + HEAD_SIZE);
}
