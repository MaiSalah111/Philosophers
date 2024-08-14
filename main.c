/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:44:09 by maiahmed          #+#    #+#             */
/*   Updated: 2024/08/14 10:11:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_break_while(t_args *args, int *i)
{
	pthread_mutex_lock(&args->sync_mutex);
	if (ft_now_ms() - args->philos[*i].last_meal_beginning
		>= (time_t)args->time2die
		|| args->total_finished == args->philo_count)
	{
		if (args->max_meals != -1 && args->total_finished == args->philo_count)
		{
			args->everybody_full = true;
			printf("Every philosopher had a minimum of %d times\n",
				args->max_meals);
		}
		else
		{
			args->death_occured = true;
			printf("%ld %d died\n",
				ft_now_ms() - args->start_time, args->philos[*i].nbr);
		}
		pthread_mutex_unlock(&args->sync_mutex);
		return (true);
	}
	if (*i + 1 == args->philo_count)
		*i = -1;
	pthread_mutex_unlock(&args->sync_mutex);
	return (false);
}

int	main(int argc, char **argv)
{
	t_args		args;
	int			i;

	memset(&args, 0, sizeof(t_args));
	if (argc < 5 || argc > 6
		|| !ft_initialize_args(&args, argv))
		return (1);
	ft_initialize_philos(&args);
	i = -1;
	while (++i < args.philo_count)
		pthread_create(&args.philos[i].thread, NULL, ph_routine, &args.philos[i]);
	i = -1;
	while (++i < args.philo_count && !ft_break_while(&args, &i))
		i = i + 0;
	i = -1;
	while (++i < args.philo_count)
		pthread_join(args.philos[i].thread, NULL);
	i = -1;
	while (++i < args.philo_count)
		pthread_mutex_destroy(&args.philos[i].l_fork);
	return (0);
}
