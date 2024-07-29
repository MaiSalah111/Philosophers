/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiahmed <maiahmed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:44:13 by maiahmed          #+#    #+#             */
/*   Updated: 2024/07/09 10:44:48 by maiahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_initialize_args(t_args *args, char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
		if (!ft_isint(argv[i]))
			return (write(2, "Error: Argument is not a valid integer\n", 39), false);
			// return (false);
	args->philo_count = ft_atoi(argv[1]);
	if (args->philo_count > 200)
		return (write(2, "Error: Philosopher count exceeds maximum limit of 200\n", 55), false);
		// return (false);
	args->time2die = ft_atoi(argv[2]);
	args->time2eat = ft_atoi(argv[3]);
	args->time2sleep = ft_atoi(argv[4]);
	args->max_meals = -1;
	if (argv[5])
	{
		args->max_meals = ft_atoi(argv[5]);
		if (!args->max_meals)
			return (write(2, "Error: Invalid maximum meals count\n", 36), false);
			// return (false);
	}
	pthread_mutex_init(&args->sync_mutex, NULL);
	args->start_time = ft_now_ms();
	return (true);
}

void	ft_initialize_philos(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philo_count)
	{
		args->philos[i].nbr = i + 1;
		args->philos[i].last_meal_beginning = args->start_time;
		pthread_mutex_init(&args->philos[i].l_fork, NULL);
		if (i + 1 == args->philo_count)
			args->philos[i].r_fork = &args->philos[0].l_fork;
		else
			args->philos[i].r_fork = &args->philos[i + 1].l_fork;
		args->philos[i].args = args;
	}
}
