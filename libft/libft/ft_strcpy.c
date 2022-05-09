/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molesen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:33:13 by molesen           #+#    #+#             */
/*   Updated: 2021/11/23 11:05:41 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*pnt;

	pnt = dest;
	while (*src != '\0')
		*pnt++ = *src++;
	*pnt = '\0';
	return (dest);
}
