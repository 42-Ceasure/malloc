
#include <stdlib.h>
#include <stdio.h>

#define HEADER_SIZE 4
#define LSB 0x00000001
#define NBR 0xFFFFFFF8
#define ALIGNMENT 8

#define HEAP_MAX 1024 * 8

char		heap[HEAP_MAX] = {0};

void	init_heap(void)
{
	int		*i = (int *)heap;

	*i = (int) HEAP_MAX;
}

void	free(void *ptr)
{
	(void)ptr;
	// check before;
	// check after;
	// merge;
	// set headfooter;
}

void	setBlockHeadFoot(int *ptr, int size)
{
	*ptr = (int)(size + 1);
	*(ptr + size) = (int)*ptr;
}

void 	*create_block(int *ptr, int size)
{
	setBlockHeadFoot((int *)ptr, size);
	printf("allocPointer:%p\n", (int *)(ptr + 1));
	return ((int *)(ptr + 1));
}

void	*find_ffit_chunk(size_t blockSize)
{
	int		*ptr;

	ptr = (int *)heap;
	while ((ptr - (int *)heap) < HEAP_MAX)
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

	padding = (ALIGNMENT - (size % ALIGNMENT));
	if (padding != ALIGNMENT)
		size += padding;
	return (size + (HEADER_SIZE * 2));
}

void	*mymalloc(size_t size)
{
	size_t		blockSize;
	void		*ptr;

	blockSize = calc_blockSize(size);
	printf("blockSize:%zu\n", blockSize);
	if (blockSize == 0 || blockSize > HEAP_MAX)
		return (NULL);
	ptr = find_ffit_chunk(blockSize);
	printf("blockPointer:%p\n", ptr);
	return (create_block(ptr, blockSize));
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
		printf("allocSize:%d\n", nb);
		test = (char *)mymalloc(sizeof(char) * nb);
		if (test !=  NULL)
		{
			test[nb] = '\0';
			while (i < nb)
			{
				test[i] = (char)(i % 10 + '0');
				i++;
			}
			printf("%s\n", test);
		}
	}
	return (0);
}
