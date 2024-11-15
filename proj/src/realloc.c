/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cpy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1789/06/15 10:55:10 by cglavieu          #+#    #+#             */
/*   Updated: 2024/10/25 10:55:12 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mymalloc.h>

void	*realloc(void *ptr, size_t size)
{
	/*

	check le pointeur,
		si invalide, return;
		si NULL, faire un mymalloc(size);

	check la size,
		si 0 et ptr non null, faire free(ptr);
		si size < taille du chunk, allouer size
		si size > taille du chunk
		regarder bloc d'apres
			s'il suffit, merge blocs, allouer size
			s'il ne suffit pas, fffit
			copier
			free precedent
	
	retourner pointeur

	*/
	(void)ptr; 
	(void)size;
	return (NULL);
}
