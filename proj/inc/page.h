/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:55:51 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/11 12:48:14 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAGE_H
# define PAGE_H

# include <stddef.h>

# define SIZE		-8
# define TYPE		-7
# define ALLOC		-6
# define NEXTP		-5
# define PREVP		-4
# define FSPACE		-3
# define LFSPACE	-2
# define SFSPACE	-1

# define PAGE_ELEMENTS 8
# define PAGE_HEADSIZE (PAGE_ELEMENTS * sizeof(size_t))

// typedef struct	s_page_header
// {
// 	size_t	size;
// 	size_t	type;
// 	size_t	allocations;
// 	void	*nextpage;
// 	void	*prevpage;
// 	size_t	freespace;
// 	size_t	largestfreespace;
// 	size_t	smallestfreespace;
// }				t_page_header;

// typedef struct	s_page
// {
// 	t_page_header	header;
// 	void			*data;
// }				t_page;


size_t	get_page_size(size_t *page);
size_t	get_page_type(size_t *page);
size_t	get_page_allocations(size_t *page);
void	*get_page_nextpage(size_t *page);
void	*get_page_prevpage(size_t *page);
size_t	get_page_freespace(size_t *page);
size_t	get_page_largestfreespace(size_t *page);
size_t	get_page_smallestfreespace(size_t *page);

void	*new_page(size_t nb);
void	*extend_page(void *page, size_t nb);
void	*get_next_page(void *page);
void	*get_prev_page(void *page);

void	dump_page(size_t *page);

#endif