/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:38:02 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/17 10:18:33 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNK_H
# define CHUNK_H

# include <stddef.h>

# include <data.h>

# define ALIGNMENT		(2 * sizeof(size_t))

# define HEAD_SIZE		(sizeof(size_t))
# define FOOT_SIZE		(HEAD_SIZE)
# define DATA_SIZE		(HEAD_SIZE + FOOT_SIZE)
# define END_CHUNK		(DATA_SIZE + ALIGNMENT)

# define CHUNK_USED		(1)
# define CHUNK_FREE		(0)

# define LSB			(0x00000001)
# define NBR			(0xFFFFFFF8)

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

#endif