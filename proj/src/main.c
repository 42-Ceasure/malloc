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
	void	*ptr[TEST];

	printf("max allocable : %d\n", USR_USABLE);
	dump_heap();
	size_t	i = 0;
	while (i < TEST)
	{
		ptr[i] = mymalloc(i * 8);
		i++;
	}
	i = 0;
	while (i < TEST)
	{
		if (i % 2 == 0)
			myfree(ptr[i]);
		i++;
	}
	ptr[0] = mymalloc(5953);
	ptr[1] = mymalloc(1);
	ptr[1] = mymalloc(1);
	ptr[1] = mymalloc(1);
	ptr[1] = mymalloc(1);
	ptr[1] = mymalloc(16);
	ptr[1] = mymalloc(112);
	ptr[1] = mymalloc(140);
	ptr[1] = mymalloc(16);
	ptr[1] = mymalloc(98);
	ptr[1] = mymalloc(97);
	myfree(ptr[0]);
	dump_heap();
	(void)ptr;
	(void)ac;
	(void)av;
	return (0);
}
