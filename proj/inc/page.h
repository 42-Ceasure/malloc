/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:55:51 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/12 12:00:17 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAGE_H
# define PAGE_H

# include <stddef.h>

# define SIZE		-4
# define ALLOC		-3
# define NEXTP		-2
# define PREVP		-1

# define PAGE_ELEMENTS 4
# define PAGE_HEADSIZE (PAGE_ELEMENTS * sizeof(size_t))

typedef enum	e_page_type
{
	TINY,
	MEDIUM,
	LARGE
}				t_ptype;

size_t	get_page_size(size_t *page);
size_t	get_page_allocations(size_t *page);
void	*get_page_nextpage(size_t *page);
void	*get_page_prevpage(size_t *page);
void	*new_page(size_t nb);
void	*extend_page(void *page, size_t nb);
void	*get_next_page(void *page);
void	*get_prev_page(void *page);

void	dump_page(size_t *page);
void	*page_manager(t_ptype type);

#endif