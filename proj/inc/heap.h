/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:50:13 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/16 07:12:24 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
# define HEAP_H

# include <stddef.h>

# include <page.h>
# include <chunk.h>

# define DEFAULT_TINY	(2)
# define DEFAULT_MEDIUM	(8)
# define DEFAULT_LARGE	(1)

# define TINY_SIZE		(64)
# define MEDIUM_SIZE	(256)

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

void	*heap_manager(t_atype type);

#endif