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

# define HEAP_MAX		(1024 * 8)
# define MAX_USABLE		(HEAP_MAX - END_CHUNK)
# define USR_USABLE		(MAX_USABLE - DATA_SIZE)

extern void *const heap;

size_t	set_chunk_size(const size_t user_size);
void	*mymalloc(size_t user_size);

void	*realloc(void *ptr, size_t size);

void	myfree(void *ptr);

void	dump_chunk_datas(void *ptr);
void	dump_chunk(void *ptr);
void	dump_heap(void);
void	init_heap(void);

size_t	get_micro_data(const void *const ptr);
void	set_micro_data(size_t *const ptr, const size_t data);

void	*find_ffit_chunk(void *ptr, const size_t size);
void	*find_lfit_chunk(void *ptr, const size_t size);

void	*jump_next_free_chunk(void *ptr);
void	*next_free_chunk(void *ptr);
void	*next_chunk(void *ptr);

void	*jump_prev_free_chunk(void *ptr);
void	*prev_free_chunk(void *ptr);
void	*prev_chunk(void *ptr);

void	*get_user_chunk(void *usr_ptr);
void	*merge_chunks(void *const ptr1, void *ptr2, const size_t status);
void	split_chunk(void *const ptr, const size_t size);

size_t	is_chunk_used(const void *const ptr);
size_t	get_chunk_size(const void *const ptr);
void	*chkptr_from_usrptr(void *user_ptr);
void	*usrptr_from_chkptr(void *ptr);

void	set_header(void *const ptr, const size_t size, const size_t status);
void	set_footer(void *const ptr, const size_t size, const size_t status);
void	set_chunk(void *const ptr, const size_t size, const size_t status);

void	set_head_ptr(void *const ptr, const size_t size);
void	set_foot_ptr(void *const ptr,  size_t size);
void	set_wormhole(void *const ptr1, void *const ptr2);

#endif