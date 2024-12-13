/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:55:51 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/13 17:16:21 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAGE_H
# define PAGE_H

# include <stddef.h>
# include <sys/mman.h>
# include <unistd.h>

# include <chunk.h>
# include <data.h>

# define PAGE_SIZE		(getpagesize())
# define PAGE_ELEMENTS	(8)
# define PAGE_HEADSIZE	(PAGE_ELEMENTS * sizeof(size_t))

# define PREVP			-8
// # define FIRST		-7
# define SIZE			-4
# define ALLOC			-3
// # define LAST		-2
# define NEXTP			-1


size_t	get_page_size(size_t *page);
size_t	get_page_allocations(size_t *page);
void	*get_page_nextpage(size_t *page);
void	*get_page_prevpage(size_t *page);
void	*new_page(size_t nb);
void	*extend_page(void *page);
void	*get_next_page(void *page);
void	*get_prev_page(void *page);
void	*header_from_page(void *page);

void	dump_page(size_t *page);

#endif