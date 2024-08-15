/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:06:57 by codespace         #+#    #+#             */
/*   Updated: 2024/08/15 10:01:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool ft_initialize_args(t_args *args, char **argv)
{
    if (!error_handler(argv))
        return (false);
    args->philo_count = ft_atoi(argv[1]);
    args->time2die = ft_atoi(argv[2]);
    args->time2eat = ft_atoi(argv[3]);
    args->time2sleep = ft_atoi(argv[4]);
    if (argv[5])
        args->max_meals = ft_atoi(argv[5]);
    else
        args->max_meals = -1;
    pthread_mutex_init(&args->sync_mutex, NULL);
    args->start_time = ft_now_ms();
    return (true);
}

// bool ft_initialize_args(t_args *args, char **argv)
// {
//     if (!error_handler(argv))
//         return (false);
//     args->philo_count = ft_atoi(argv[1]);
//     args->time2die = ft_atoi(argv[2]);
//     args->time2eat = ft_atoi(argv[3]);
//     args->time2sleep = ft_atoi(argv[4]);
//     args->max_meals = argv[5] ? ft_atoi(argv[5]) : -1;
//     pthread_mutex_init(&args->sync_mutex, NULL);
//     args->start_time = ft_now_ms();
//     return (true);
// }

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