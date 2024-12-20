/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:59:38 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/20 11:07:22 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

int		main(int ac, char **av)
{
	printf("-------\nentering:%s\n-------\n", __func__);
	void 	*page1 = NULL;
	size_t	page1nb = 1;
	size_t	page1size = page1nb * SYS_PAGESIZE;
	void 	*page2 = NULL;
	size_t	page2nb = 2;
	size_t	page2size = page2nb * SYS_PAGESIZE;

	if (ac > 1)
		(void)av;
	page1 = new_page(page1nb);
	init_page(page1, page1size, 0);
	page2 = new_page(page2nb);
	init_page(page2, page2size, 2);
	link_pages(page1, page2);
	dump_page(page1);
	dump_page(page2);
	return (0);
}