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

int		is_chunk_used(const void *ptr)
{
	return (*(size_t *)ptr & LSB);
}

size_t	get_chunk_size(const void *ptr)
{
	return (*(size_t *)ptr & NBR);
}

void	*chunk_from_usrptr(void *ptr)
{
	return (ptr - HEAD_SIZE);
}

void	*usrptr_from_chunk(void *ptr)
{
	return (ptr + HEAD_SIZE);
}
