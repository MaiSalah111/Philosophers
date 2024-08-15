/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:04:42 by codespace         #+#    #+#             */
/*   Updated: 2024/08/15 18:07:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	handle_single_philo(t_philo *philo)
{
	printf("%ld %d has taken a fork\n",
		ft_now_ms() - philo->args->start_time, philo->nbr);
	ft_usleep(philo->args->time2die, philo);
	return (false);
}

bool	handle_even_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (!ft_write_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->r_fork);
		return (false);
	}
	pthread_mutex_lock(&philo->l_fork);
	if (!ft_write_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);
		return (false);
	}
	return (true);
}

bool	handle_odd_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	if (!ft_write_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(&philo->l_fork);
		return (false);
	}
	return (true);
}

bool	pick_forks(t_philo *philo)
{
	if (philo->args->philo_count == 1)
		return (handle_single_philo(philo));
	if (should_stop(philo))
		return (false);
	if (philo->nbr % 2 == 0)
		return (handle_even_philo(philo));
	else
		return (handle_odd_philo(philo));
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
