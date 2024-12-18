/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymalloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/18 11:31:20 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# include <sys/mman.h>
# include <unistd.h>

/* **************** */
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
/* **************** */

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

# define DEFAULT_TINY	(2)
# define DEFAULT_MEDIUM	(8)
# define DEFAULT_LARGE	(1)

# define TINY_SIZE		(64)
# define MEDIUM_SIZE	(256)

# define PAGE_SIZE		(getpagesize())
# define PAGE_ELEMENTS	(4)
# define PAGE_HEADSIZE	(PAGE_ELEMENTS * sizeof(size_t))

# define PREVP			-4
# define SIZE			-3
# define ALLOC			-2
# define NEXTP			-1

typedef enum	e_alloc_type
{
	TINY,
	MEDIUM,
	LARGE
}				t_atype;

typedef	struct	s_heap
{
	void	*tiny;
	void	*medium;
	void	*large;
}				t_heap;

extern	t_heap	*g_heap;

void	*getmap(const size_t len);

void	inc_page_allocations(size_t *page);
void	dec_page_allocation(size_t *page);
size_t	get_page_size(size_t *page);
size_t	get_page_usable_size(size_t *page);
size_t	get_page_allocations(size_t *page);
void	*get_page_nextpage(size_t *page);
void	*get_page_prevpage(size_t *page);
void	*new_page(size_t nb);
void	*new_specific_page(size_t size);
void	*extend_page(void *page);
void	*get_next_page(void *page);
void	*get_prev_page(void *page);
size_t	is_page_inited(void *page);
void	*header_from_page(void *page);
void	*page_manager(void *page);

void	dump_page(size_t *page);

void	*heap_manager(t_atype type);

size_t	get_micro_data(const void *const ptr);
void	set_micro_data(size_t *const ptr, const size_t data);
void	*get_adress(size_t *adress);
void	write_adress(size_t *where, size_t *adress);

size_t	get_chunk_status(const void *const ptr);
size_t	get_chunk_size(const void *const ptr);
void	*chkptr_from_usrptr(void *user_ptr);
void	*usrptr_from_chkptr(void *ptr);

void	set_header(void *const ptr, const size_t size, const size_t status);
void	set_footer(void *const ptr, const size_t size, const size_t status);
void	set_chunk(void *const ptr, const size_t size, const size_t status);
void	init_page_chunks(void *ptr, size_t size);

void	*find_ffit_chunk(void *ptr, const size_t size);
void	*find_lfit_chunk(void *ptr, const size_t size);

void	*get_user_page(void *usr_ptr);
void	*merge_chunks(void *const ptr1, void *ptr2, const size_t status);
void	split_chunk(void *const ptr, const size_t size);
void	*chunk_manager(void **page, size_t size);

void	*jump_prev_free_chunk(void *start, void *ptr);
void	*prev_free_chunk(void *start, void *ptr);
void	*prev_chunk(void *start, void *ptr);

void	*jump_next_free_chunk(void *ptr);
void	*next_free_chunk(void *ptr);
void	*next_chunk(void *ptr);

void	set_head_ptr(void *const ptr, const size_t size);
void	set_foot_ptr(void *const ptr,  size_t size);
void	set_wormhole(void *const ptr1, void *const ptr2);

size_t	aligned_size(const size_t user_size);
void	allocate(void *heap, void *const ptr, const size_t size);
void	*mymalloc(size_t user_size);

void	*myrealloc(void *ptr, size_t size);

void	deallocate(void *start, void *ptr);
void	myfree(void *ptr);

void	dump_chunk_datas(void *ptr);
void	dump_chunk(void *ptr);
void	dump_chunks(void *ptr);
void	dump_heap(void);

size_t	get_micro_data(const void *const ptr);
void	set_micro_data(size_t *const ptr, const size_t data);
void	*get_adress(size_t *adress);
void	write_adress(size_t *where, size_t *adress);

#endif