/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:55:51 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/10 16:22:34 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAGE_H
# define PAGE_H

# include <stddef.h>

# define SIZE		0
# define TYPE		1
# define ALLOC		2
# define NEXTP		3
# define PREVP		4
# define FSPACE		5
# define LFSPACE	6
# define SFSPACE	7

typedef struct	s_page_header
{
	size_t	size;
	size_t	type;
	size_t	allocations;
	void	*nextpage;
	void	*prevpage;
	size_t	freespace;
	size_t	largestfreespace;
	size_t	smallestfreespace;
}				t_page_header;

# define PAGE_HEADSIZE (sizeof(t_page_header))

void	*getXpages(const size_t x);
void	*get_page(size_t nb);
void	dump_page(size_t *ptr);

#endif