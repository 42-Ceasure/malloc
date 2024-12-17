/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymalloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/17 12:26:34 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>

/* **************** */
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
/* **************** */

# include <heap.h>
# include <chunk.h>
# include <page.h>

# define DEBUG			(1)

extern	t_heap	*g_heap;

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