/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/10 12:56:21 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

size_t	get_micro_data(const void *const ptr)
{
	return (*(size_t *)ptr);
}

void	set_micro_data(size_t *const ptr, const size_t data)
{
	*ptr = data;
}

void	*get_adress(size_t *adress)
{
	size_t number;

	number = *adress;
	return ((void *)number);
}

void	write_adress(size_t *where, size_t *adress)
{
	size_t	number;

	number = (size_t)adress;
	*where = number;
}
