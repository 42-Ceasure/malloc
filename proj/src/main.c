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
#define TEST 20

int main(int ac, char **av)
{
	init_heap();
	char	*ptr[TEST];
	size_t	i = 0;

	dump_heap();
	while (i < TEST)
	{
		ptr[i] = mymalloc(i * 7);
		i++;
	}
	dump_heap();
	(void)ptr;
	(void)ac;
	(void)av;
	return (0);
}
