/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:16:22 by codespace         #+#    #+#             */
/*   Updated: 2024/08/14 15:13:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
    size_t		i;
    int			sign;
    long int	sum;

    i = 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
           str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
        i++;
    sign = 1;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    sum = 0;
    while (str[i] >= '0' && str[i] <= '9')
    {
        sum = sum * 10 + (str[i] - '0');
        if (sum < 0)
            return ((sign != -1) * -1);
        i++;
    }
    return (sum * sign);
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

bool	ft_isint(char *str)
{
	char	*max_int;
	size_t	str_len;

	max_int = "2147483647";
	if (*str == '+')
		str++;
	str_len = ft_strlen(str);
	if (str_len > 10)
		return (false);
	if (str_len == 10)
		while (ft_isdigit(*str) && *str <= *max_int++)
			str++;
	else
		while (ft_isdigit(*str))
			str++;
	return (!*str && true);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
