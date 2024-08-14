/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 07:37:19 by codespace         #+#    #+#             */
/*   Updated: 2024/08/14 07:59:53 by codespace        ###   ########.fr       */
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
