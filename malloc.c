
#include <stdlib.h>
#include <stdio.h>

#define HEADER_SIZE 8
#define LSB 0x00000001
#define NBR 0xFFFFFFF8

#define HEAP_MAX 1024 * 8

char		heap[HEAP_MAX] = {0};

void	init_heap(void)
{
	int		*i = (int *)heap;

	*i = (int) HEAP_MAX;
}

void	setBlockHeadFoot(int *ptr, int size)
{
	*ptr = (int)(size + 1);
	*(ptr + size) = (int)*ptr;
}

void 	*create_block(int *ptr, int size)
{
	setBlockHeadFoot((int *)ptr, size);
	return ((int *)(ptr + 1));
}

void	free(void *ptr)
{
	(void)ptr;
	// check before;
	// check after;
	// merge;
	// set headfooter;
}

void	*find_ffit_chunk(size_t blockSize)
{
	int stop = 0;
	int		*ptr;

	ptr = (int *)heap;
	while ((ptr - (int *)heap < HEAP_MAX) && stop++ < 10)
	{
		if ((*ptr & LSB) != 1 && (*ptr & NBR) >= blockSize)
			return (ptr);
		else
			ptr += *ptr & NBR;

	}
	return (NULL);
}

size_t	calc_blockSize(size_t size)
{
	int		padding;

	padding = (8 - (size % 8));
	if (padding != 8)
		size += padding;
	return (size + (HEADER_SIZE * 2));
}

void	*mymalloc(int size)
{
	size_t		blockSize;
	void		*ptr;

	if (size > 0)
	{
		blockSize = calc_blockSize(size);
		ptr = find_ffit_chunk(blockSize);
		return (create_block(ptr, blockSize));
	}
	return (NULL);
}

int main(int ac, char **av)
{
	int		i = 0;
	int		nb;
	char	*test;

	init_heap();
	if (ac > 1)
	{
		nb = atoi(av[1]);
		test = (char *)mymalloc(sizeof(char) * nb + 1);
		if (test !=  NULL && nb > 0)
		{
			test[nb] = '\0';
			while (i < nb)
				test[i++] = '1';
			printf("%s\n", test);
		}
	}
	return (0);
}