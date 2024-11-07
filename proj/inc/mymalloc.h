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

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <stdio.h>

# define ALIGNMENT		16

# define HEAD_SIZE		8
# define FOOT_SIZE	HEAD_SIZE

# define CHUNK_USED		1
# define CHUNK_FREE		0

# define LSB			0x00000001
# define NBR			0xFFFFFFF8

# define HEAP_MAX		1024 * 8
# define MAX_USABLE		HEAP_MAX - (HEAD_SIZE + FOOT_SIZE)

extern char heap[HEAP_MAX];

typedef struct	s_chunk
{
	size_t	*ptr;
	size_t	size;
}				t_chunk;

void	init_heap(void);
void	dump_heap(void);
void	*mymalloc(size_t size);
void	*find_ffit_chunk(size_t *ptr, size_t size);
void	*next_chunk(char *ptr);
size_t	get_chunk_size(size_t *ptr);
int		is_chunk_free(size_t *ptr);
void	split_chunk(size_t *ptr, size_t size);
void	*create_block(size_t *ptr, size_t size, size_t used);


#endif