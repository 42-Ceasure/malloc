/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymalloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/10 11:13:30 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stddef.h>

/* **************** */
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
/* **************** */

# include <chunk.h>
# include <page.h>

# define DEBUG			(1)

# define ALIGNMENT		(2 * sizeof(size_t))

# define HEAD_SIZE		(sizeof(size_t))
# define FOOT_SIZE		(HEAD_SIZE)
# define DATA_SIZE		(HEAD_SIZE + FOOT_SIZE)
# define END_CHUNK		(DATA_SIZE + ALIGNMENT)

# define CHUNK_USED		(1)
# define CHUNK_FREE		(0)

# define LSB			(0x00000001)
# define NBR			(0xFFFFFFF8)

# define PAGE_SIZE		(getpagesize())

typedef	struct	s_heap
{
	void	*tiny;
	void	*medium;
	void	*large;
}				t_heap;

extern	t_heap	*g_heap;

size_t	set_chunk_size(const size_t user_size);
void	allocate(void *const ptr, const size_t size);
void	*mymalloc(size_t user_size);

void	*myrealloc(void *ptr, size_t size);

void	deallocate(void *ptr);
void	myfree(void *ptr);

void	dump_chunk_datas(void *ptr);
void	dump_chunk(void *ptr);
void	dump_heap(void *ptr);
void	init_heap(void);

size_t	get_micro_data(const void *const ptr);
void	set_micro_data(size_t *const ptr, const size_t data);
void	*get_adress(size_t *adress);
void	write_adress(size_t *where, size_t *adress);

#endif