/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymalloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/12/20 08:45:21 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/types.h>	// define size_t
# include <sys/mman.h>	// include mmap
# include <stddef.h>	// include NULL
# include <unistd.h>	// include getpagesize()

/*--\outlaw includes/--*/
# include <stdio.h>
/*---------------------*/

# include <page.h>

# define DEBUG			(1)

#endif