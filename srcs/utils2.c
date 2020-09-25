/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:19:51 by kallard           #+#    #+#             */
/*   Updated: 2020/09/25 15:43:11 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*safe_str_join(char *str1, const char *str2)
{
	char *str_result;

	str_result = ft_strjoin(str1, str2);
	free(str1);
	return (str_result);
}
