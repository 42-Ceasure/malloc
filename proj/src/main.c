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

void	testzarb()
{
	printf("-----\nentering %s\n", __func__);

	void	*ptr[TEST];
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
	dump_heap();
	ptr[0] = mymalloc(5953);
	dump_heap();
	myfree(ptr[0]);
	dump_heap();
	ptr[1] = mymalloc(1);
	ptr[1] = mymalloc(1);
	ptr[1] = mymalloc(1);
	ptr[1] = mymalloc(1);
	ptr[1] = mymalloc(16);
	dump_heap();
	ptr[1] = mymalloc(112);
	ptr[1] = mymalloc(140);
	ptr[1] = mymalloc(16);
	ptr[1] = mymalloc(98);
	ptr[1] = mymalloc(97);
	ptr[0] = mymalloc(47);
	ptr[0] = mymalloc(47);
	ptr[0] = mymalloc(47);
	ptr[0] = mymalloc(47);
	ptr[1] = mymalloc(15);
	ptr[1] = mymalloc(15);
	ptr[1] = mymalloc(6000);
	ptr[1] = mymalloc(15);
	if (ptr[1] == NULL)
		printf("c'est MORT\n");
	dump_heap();
	printf("leaving %s\n-----\n", __func__);
}

int main(int ac, char **av)
{
	char	**ptr;
	size_t	i = 0;

	printf("max allocable : %d\n", USR_USABLE);
	init_heap();
	dump_heap();
	testzarb();
	ptr = (char **)mymalloc(sizeof(char *) * TEST);
	if (ptr != NULL)
	{
		printf("pointer tab initialised\n");
		dump_heap();
/* ************************************************************************** */

		while (i < TEST)
		{
			ptr[i] = (char *)mymalloc(sizeof(char) * 15 + i + 1);
			size_t j = 0;
			while (j < 15 + i)
			{
				ptr[i][j] = 'X';
				j++;
			}
			ptr[i][j] = '\0';
			printf("%s\n", ptr[i]);
			i++;
		}
		dump_heap();
		while(i)
			myfree(ptr[--i]);

/* ************************************************************************** */
		myfree(ptr);
	}
	dump_heap();





	(void)ptr;
	(void)ac;
	(void)av;
	return (0);
}
