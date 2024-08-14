/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:44:13 by maiahmed          #+#    #+#             */
/*   Updated: 2024/08/14 08:14:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_validate_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (!ft_isint(argv[i]))
			return (write(2, "Error: Invalid Argument\n", 25), false);
	}
	return (true);
}

static bool	ft_validate_philo_count(int philo_count)
{
	if (philo_count > 200)
	{
		write(2, "Error: Philosopher count exceeds maximum limit of 200\n", 55);
		return (false);
	}
	return (true);
}

static bool	ft_set_max_meals(t_args *args, char **argv)
{
	if (argv[5])
	{
		args->max_meals = ft_atoi(argv[5]);
		if (!args->max_meals)
		{
			write(2, "Error: Invalid maximum meals count\n", 36);
			return (false);
		}
	}
	else
		args->max_meals = -1;
	return (true);
}

bool	ft_initialize_args(t_args *args, char **argv)
{
	if (!ft_validate_args(argv))
		return (false);
	args->philo_count = ft_atoi(argv[1]);
	if (!ft_validate_philo_count(args->philo_count))
		return (false);
	args->time2die = ft_atoi(argv[2]);
	args->time2eat = ft_atoi(argv[3]);
	args->time2sleep = ft_atoi(argv[4]);
	if (!ft_set_max_meals(args, argv))
		return (false);
	pthread_mutex_init(&args->sync_mutex, NULL);
	args->start_time = ft_now_ms();
	return (true);
}



