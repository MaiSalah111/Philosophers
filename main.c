/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:44:09 by maiahmed          #+#    #+#             */
/*   Updated: 2024/08/15 18:06:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	create_philosophers(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philo_count)
		pthread_create(&args->philos[i].thread, NULL,
			ph_routine, &args->philos[i]);
	return (true);
}

static bool	join_philosophers(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philo_count)
		pthread_join(args->philos[i].thread, NULL);
	return (true);
}

static bool	destroy_forks(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philo_count)
		pthread_mutex_destroy(&args->philos[i].l_fork);
	return (true);
}

static bool	monitor_simulation(t_args *args)
{
	int	i;

	i = -1;
	if (args->philo_count > 1)
	{
		while (++i < args->philo_count && !ck_simulation_status(args, &i))
		{
			usleep(1);
			i = i + 0;
		}
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_args	args;

	memset(&args, 0, sizeof(t_args));
	if (argc < 5 || argc > 6 || !ft_initialize_args(&args, argv))
		return (1);
	ft_initialize_philos(&args);
	create_philosophers(&args);
	monitor_simulation(&args);
	join_philosophers(&args);
	destroy_forks(&args);
	return (0);
}
