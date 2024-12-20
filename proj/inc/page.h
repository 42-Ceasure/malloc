/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:55:51 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/20 09:18:55 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAGE_H
# define PAGE_H

# include <stddef.h>
# include <sys/mman.h>
# include <unistd.h>
# include <stdio.h>

# include <data.h>
# include <chunk.h>

# define PAGE_SIZE		(getpagesize())
# define PAGE_ELEMENTS	(4)
# define PAGE_HEADSIZE	(PAGE_ELEMENTS * sizeof(size_t))

# define PREVP			-4
# define SIZE			-3
# define ALLOC			-2
# define NEXTP			-1

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

#endif