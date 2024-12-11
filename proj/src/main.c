/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/11 12:33:15 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>
#define TEST 20

void	testzarb()
{
	printf("-----\nentering %s\n", __func__);

	void	*ptr[TEST];
	void	*ptr2[TEST];
	size_t	i = 0;

	while (i < TEST)
	{
		ptr[i] = mymalloc(i * 8);
		i++;
	}
	dump_heap(g_heap->tiny);
	i = 0;
	while (i < TEST)
	{
		if (i % 2 == 0)
		{
			myfree(ptr[i]);
			ptr[i] = NULL;
		}
		i++;
	}
	dump_heap(g_heap->tiny);
	i = 0;
	ptr2[i] = mymalloc(5953);
	dump_heap(g_heap->tiny);
	myfree(ptr2[i]);
	ptr2[i++] = NULL;
	dump_heap(g_heap->tiny);
	ptr2[i++] = mymalloc(1);
	ptr2[i++] = mymalloc(1);
	ptr2[i++] = mymalloc(1);
	ptr2[i++] = mymalloc(1);
	ptr2[i++] = mymalloc(16);
	dump_heap(g_heap->tiny);
	ptr2[i++] = mymalloc(112);
	ptr2[i++] = mymalloc(140);
	ptr2[i++] = mymalloc(16);
	ptr2[i++] = mymalloc(98);
	ptr2[i++] = mymalloc(97);
	ptr2[i++] = mymalloc(47);
	ptr2[i++] = mymalloc(47);
	ptr2[i++] = mymalloc(47);
	ptr2[i++] = mymalloc(47);
	ptr2[i++] = mymalloc(15);
	ptr2[i++] = mymalloc(15);
	ptr2[i++] = mymalloc(5000);
	ptr2[i++] = mymalloc(15);
	ptr2[i++] = mymalloc(123);
	dump_heap(g_heap->tiny);
	i = 0;
	while (i < TEST)
	{
		myfree(ptr[i]);
		myfree(ptr2[i]);
		i++;
	}
	dump_heap(g_heap->tiny);
	printf("leaving %s\n-----\n", __func__);
}

void	anotherweirdtest()
{
	char	**ptr;
	size_t	i = 0;

	ptr = (char **)mymalloc(sizeof(char *) * TEST);
	if (ptr != NULL)
	{
		printf("pointer tab initialised\n");
		dump_heap(g_heap->tiny);
/* ************************************************************************** */

		while (i < TEST)
		{
			ptr[i] = (char *)mymalloc(sizeof(char) * 15 + i + 1);
			if (ptr[i])
			{
				size_t j = 0;
				while (j < 15 + i)
				{
					ptr[i][j] = 'X';
					j++;
				}
				ptr[i][j] = '\0';
				printf("%s\n", ptr[i]);
			}
			i++;
		}
		dump_heap(g_heap->tiny);
		while(i)
			myfree(ptr[--i]);

/* ************************************************************************** */
		myfree(ptr);
	}
	dump_heap(g_heap->tiny);

/* ************************** testing realloc ******************************* */
	ptr[0] = mymalloc(45);
	ptr[1] = mymalloc(45);
	ptr[2] = mymalloc(45);
	ptr[3] = mymalloc(45);
	dump_heap(g_heap->tiny);
	myrealloc(ptr[0], 68);
	dump_heap(g_heap->tiny);
}

void	writepointertest()
{
	char heap[64];
	char heap2[64];
	char heap3[64];
	void *tmp = heap;
	void *tmp2 = heap2;
	// void *tmp3 = heap3;

	printf("heap\t:%p\n", heap);
	printf("heap2\t:%p\n", heap2);
	printf("heap3\t:%p\n", heap3);
	write_adress(tmp, tmp2);
	write_adress(tmp + 8, NULL);

	void	*test = get_adress(tmp);
	void	*test2 = get_adress(tmp + 8);
	printf("test\t:%p\n", test);
	printf("test2\t:%p\n", test2);
	printf("%zu\n", (size_t)(tmp + 8));
}

void	testpage()
{
	void	*page;
	size_t	nb;

	nb = 1;
	extend_page(g_heap->tiny, nb);
	page = g_heap->tiny;
	dump_page(page);
	page = get_next_page(page);
	dump_page(page);
	page = get_next_page(page);
	dump_page(page);
}

int main(int ac, char **av)
{
	init_heap();
	// testpage();
	testzarb();
	anotherweirdtest();
	// writepointertest();
	(void)ac;
	(void)av;
	return (0);
}
