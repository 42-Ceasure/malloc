/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:01:09 by cglavieu          #+#    #+#             */
/*   Updated: 2025/02/14 13:08:05 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define TINY_SIZE		(64)
# define MEDIUM_SIZE	(256)

# define ALIGNMENT		(2 * sizeof(size_t))
# define HEAD_SIZE		(sizeof(size_t))
# define FOOT_SIZE		(HEAD_SIZE)
# define DATA_SIZE		(HEAD_SIZE + FOOT_SIZE)

typedef enum	e_alloc_type
{
	TINY,
	MEDIUM,
	LARGE
}				t_type;

void	*chunk_manager(void *page, size_t size)
{
	void	*zone;
	/*
	
	*/
	return (zone);
}

void	*page_manager(t_type type, size_t size)
{
	void	*page;
	void	*root;

	page = NULL;
	if (!is_type_inited(type))
		set_type_root(type);
	root = get_type_root(type);
	page = find_fit_page(root, size);
	if (!page)
		page = extend_root(root);
	if (!page)
		return (NULL);
	return (page);
}

t_type	type_manager(size_t size)
{
	t_type type;

	if (size <= TINY_SIZE)
		type = TINY;
	else if (size <= MEDIUM_SIZE)
		type = MEDIUM;
	else
		type = LARGE;
	return (type);	
}

size_t	size_manager(const size_t user_size)
{
	size_t	padding;

	padding = (ALIGNMENT - (user_size % ALIGNMENT));
	if (padding == ALIGNMENT)
		padding = 0;
	return (user_size + padding + DATA_SIZE);
}

void	*my_malloc(size_t user_size)
{
	size_t	size;
	t_type	type;
	void	*page;
	void	*zone;

	if (user_size < 1)
		return (NULL);
	size = size_manager(user_size);
	type = type_manager(size);
	page = page_manager(type, size);
	if (page == NULL)
		return (NULL);
	zone = chunk_manager(page, size);
	if (zone == NULL)
		return (NULL);
	// else incremente page allocations
	return (zone);
}

int		main(void)
{
	void	*ptr;
	size_t	x;

	ptr = mymalloc(x);
}
