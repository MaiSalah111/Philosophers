/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:04:42 by codespace         #+#    #+#             */
/*   Updated: 2024/08/14 15:29:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	pick_forks(t_philo *philo)
{
	if (philo->args->philo_count == 1)
	{
		printf("%ld %d has taken a fork\n", ft_now_ms() - philo->args->start_time, philo->nbr);
		ft_usleep(philo->args->time2eat, philo);
		return (false);
	}
	if (should_stop(philo))
		return (false);
	if (~(philo->nbr & 1))
	{
		pthread_mutex_lock(&philo->l_fork);
		if (!ft_write_status(philo, "has taken a fork"))
		{
			pthread_mutex_unlock(&philo->l_fork);
			return (false);
		}
		pthread_mutex_lock(philo->r_fork);
		if (!ft_write_status(philo, "has taken a fork"))
		{
			pthread_mutex_unlock(&philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			return (false);
		}
	}
	else
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
			pthread_mutex_unlock(&philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			return (false);
		}
	}
	return (true);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

// bool	pick_forks(t_philo *philo)
// {
// 	if (philo->args->philo_count == 1)
// 	{
// 		printf("%ld %d has taken a fork\n", ft_now_ms() - philo->args->start_time, philo->nbr);
// 		ft_usleep(philo->args->time2eat, philo);
// 		return (false);
// 	}
// 	if (should_stop(philo))
// 		return (false);
// 	pthread_mutex_lock(&philo->l_fork);
// 	if (!ft_write_status(philo, "has taken a fork"))
// 	{
// 		pthread_mutex_unlock(&philo->l_fork);
// 		return (false);
// 	}
// 	if (should_stop(philo))
// 	{
// 		pthread_mutex_unlock(&philo->l_fork);
// 		return (false);
// 	}
// 	pthread_mutex_lock(philo->r_fork);
// 	if (!ft_write_status(philo, "has taken a fork"))
// 	{
// 		pthread_mutex_unlock(&philo->l_fork);
// 		pthread_mutex_unlock(philo->r_fork);
// 		return (false);
// 	}
// 	return (true);
// }