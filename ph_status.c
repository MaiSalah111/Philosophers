/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:07:20 by codespace         #+#    #+#             */
/*   Updated: 2024/08/14 15:24:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->sync_mutex);
	if (philo->args->someone_died || philo->args->all_full)
	{
		pthread_mutex_unlock(&philo->args->sync_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->args->sync_mutex);
	return (false);
}

bool	ft_write_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->args->sync_mutex);
	if (philo->args->someone_died || philo->args->all_full)
	{
		pthread_mutex_unlock(&philo->args->sync_mutex);
		return (false);
	}
	printf("%ld %d %s\n", ft_now_ms() - philo->args->start_time, philo->nbr, msg);
	pthread_mutex_unlock(&philo->args->sync_mutex);
	return (true);
}
