/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiahmed <maiahmed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 22:04:45 by maiahmed          #+#    #+#             */
/*   Updated: 2024/08/15 22:04:48 by maiahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	error_handler(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX
		|| ft_atoi(argv[1]) <= 0 || !ft_isint(argv[1]))
		return (write(2, "Invalid philo number_Max200\n", 28), false);
	if (ft_atoi(argv[2]) < 60 || !ft_isint(argv[2]))
		return (write(2, "Invalid time to die\n", 21), false);
	if (ft_atoi(argv[3]) < 60 || !ft_isint(argv[3]))
		return (write(2, "Invalid time to eat\n", 21), false);
	if (ft_atoi(argv[4]) < 60 || !ft_isint(argv[4]))
		return (write(2, "Invalid time to sleep\n", 22), false);
	if (argv[5] && (ft_atoi(argv[5]) <= 0 || !ft_isint(argv[5])))
	{
		write(2, "Invalid num of time each philo should eat\n", 42);
		return (false);
	}
	return (true);
}
