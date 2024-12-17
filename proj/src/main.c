/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/17 15:25:10 by cglavieu         ###   ########.fr       */
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
	dump_heap();
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
	dump_heap();
	i = 0;
	ptr2[i++] = mymalloc(5953);
	dump_heap();
	// myfree(ptr2[i]);
	// ptr2[i++] = NULL;
	dump_heap();
	ptr2[i++] = mymalloc(1);
	ptr2[i++] = mymalloc(1);
	ptr2[i++] = mymalloc(1);
	ptr2[i++] = mymalloc(1);
	ptr2[i++] = mymalloc(16);
	dump_heap();
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
	dump_heap();
	i = 0;
	while (i < TEST)
	{
		myfree(ptr[i]);
		myfree(ptr2[i]);
		i++;
	}
	dump_heap();
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
		dump_heap();
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
				// printf("%s\n", ptr[i]);
			}
			i++;
		}
		dump_heap();
		while(i)
			myfree(ptr[--i]);

/* ************************************************************************** */
		myfree(ptr);
	}
	dump_heap();

/* ************************** testing realloc ******************************* */
	// ptr[0] = mymalloc(45);
	// ptr[1] = mymalloc(45);
	// ptr[2] = mymalloc(45);
	// ptr[3] = mymalloc(45);
	// dump_heap();
	// myrealloc(ptr[0], 68);
	// dump_heap();
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
	return ;
}

void	testspam()
{
	size_t spamnb = 600;
	size_t i = 0;
	void *ptr[spamnb];

	while (i < spamnb)
	{
		ptr[i] = mymalloc(48);
		i++;
	}
	dump_heap();
	i = 0;
	while (i < spamnb)
	{
		ptr[i] = mymalloc(48);
		i++;
	}
	dump_heap();
}

void	testlargealloc(char *nbr)
{
	void	*ptr;

	ptr = mymalloc(atoi(nbr));
}

int main(int ac, char **av)
{
	// testpage();
	// testspam();
	testzarb();
	// anotherweirdtest();
	// writepointertest();
	// if (ac > 1)
	// 	testlargealloc(av[1]);
	(void)ac;
	(void)av;
	return (0);
}
