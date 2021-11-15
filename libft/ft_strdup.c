/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:53:15 by cfiliber          #+#    #+#             */
/*   Updated: 2021/03/04 16:55:17 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	void	*ptr;
	size_t	tot_size;

	tot_size = sizeof(const char) * (ft_strlen(s1) + 1);
	if (!(ptr = malloc(tot_size)))
		return (0);
	ft_memcpy(ptr, s1, tot_size);
	return (ptr);
}
