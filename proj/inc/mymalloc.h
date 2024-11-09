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

# define ALIGNMENT		(16)

# define HEAD_SIZE		(8)
# define FOOT_SIZE		(HEAD_SIZE)
# define DATA_SIZE		(HEAD_SIZE + FOOT_SIZE)

# define CHUNK_USED		(1)
# define CHUNK_FREE		(0)

# define LSB			(0x00000001)
# define NBR			(0xFFFFFFF8)

# define HEAP_MAX		(1024 * 8)
# define MAX_USABLE		(HEAP_MAX - DATA_SIZE)
# define USR_USABLE		(MAX_USABLE - DATA_SIZE)

extern void *const heap;

void	*mymalloc(size_t user_size);
size_t	set_chunk_size(const size_t user_size);

void	myfree(void *ptr);

void	init_heap(void);
void	dump_heap(void);
void	dump_chunk_datas(void *ptr);
void	dump_chunk(void *ptr);

void	*find_ffit_chunk(void *ptr, const size_t size);

int		is_chunk_used(const void *ptr);
size_t	get_chunk_size(const void *ptr);
void	*prev_free_chunk(void *ptr);
void	*prev_chunk(void *ptr);
void	*jump_next_free_chunk(void *ptr);
void	*next_free_chunk(void *ptr);
void	*next_chunk(void *ptr);
void	*chunk_from_usrptr(void *user_ptr);
void	*usrptr_from_chunk(void *ptr);

void	set_header(size_t *ptr, const size_t size, const size_t status);
void	set_footer(void *ptr, const size_t size, const size_t status);
void	set_chunk(void *ptr, const size_t size, const size_t status);
void	*merge_chunks(void *ptr1, void *ptr2, const size_t status);
void	split_chunk(void *ptr, const size_t size);
void	set_wormhole(void *ptr1, void *ptr2);
void	set_fast_speed(void *ptr);

#endif