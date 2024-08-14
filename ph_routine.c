/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:02:48 by codespace         #+#    #+#             */
/*   Updated: 2024/08/14 16:05:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	if (!ft_write_status(philo, "is eating 🍽️ 😋"))
		return;
	pthread_mutex_lock(&philo->args->sync_mutex);
	philo->meals_count++;
	philo->last_meal_beginning = ft_now_ms();
	if (philo->meals_count == philo->args->max_meals)
	{
		philo->args->total_finished++;
		if (philo->args->total_finished == philo->args->philo_count)
			philo->args->all_full = true;
	}
	pthread_mutex_unlock(&philo->args->sync_mutex);
	ft_usleep(philo->args->time2eat, philo);
	release_forks(philo);
}

bool	sleep_then_think(t_philo *philo)
{
	if (!ft_write_status(philo, "is sleeping 😴"))
		return (false);
	ft_usleep(philo->args->time2sleep, philo);
	if (!ft_write_status(philo, "is thinking 🧠🤔"))
		return (false);
	return (true);
}

void	*ph_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->args->philo_count == 1)
	{
		printf("%ld %d has taken a fork\n", ft_now_ms() - philo->args->start_time, philo->nbr);
		ft_usleep(philo->args->time2die, philo);
		printf("%ld %d died\n", ft_now_ms() - philo->args->start_time, philo->nbr);
		return (NULL);
	}
	if (!(philo->nbr & 1))
		ft_usleep(100, philo);
	while (1)
	{
		if (!pick_forks(philo))
			break ;
		ft_eat(philo);
		if (!sleep_then_think(philo))
			break ;
	}
	return (NULL);
}
