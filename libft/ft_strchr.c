/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:52:44 by cfiliber          #+#    #+#             */
/*   Updated: 2021/02/25 19:52:59 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	car;
	size_t	i;
	int		slen;
	char	*s2;

	car = (char)c;
	slen = ft_strlen(s);
	s2 = (char *)s;
	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == car)
			return (s2 + i);
		i++;
	}
	return (0);
}
