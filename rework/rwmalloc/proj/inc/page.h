/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/20 11:06:25 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAGE_H
# define PAGE_H

# include <sys/types.h>	// define size_t
# include <sys/mman.h>	// include mmap
# include <stddef.h>	// include NULL
# include <unistd.h>	// include getpagesize()

/*----\ outlaw includes /----*/
# include <stdio.h>
/*---------------------------*/

# define SYS_PAGESIZE		(getpagesize())

/*---     PAGE_HEADER     ---*/
/*--- 8 bytes range index ---*/
# define PAGEPREV		(0)
# define PAGENEXT		(1)
# define PAGESIZE		(2)
# define PAGETYPE		(3)
# define PAGEALLOC		(4)
/*---------------------------*/

typedef	enum	e_page_elements
{
	PREV,
	NEXT,
	SIZE,
	TYPE,
	ALLOC
}				t_pe;

/*- create/delete/set page  -*/
void			*new_page(const size_t nb);
void			del_page(void *page);
void			init_page(void *page, const size_t size, const size_t type);
/*- poll page ---------------*/
void			*get_page_linked(void *page, t_pe element);
size_t			get_page_info(void *page, t_pe element);
/*- operate on page ---------*/
void			increment_page_alloc(void *page);
void			decrement_page_alloc(void *page);
void			link_pages(void *page1, void *page2);
/*- print pages infos -------*/
void			dump_page(void *page);

#endif
