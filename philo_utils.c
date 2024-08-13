/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiahmed <maiahmed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:44:17 by maiahmed          #+#    #+#             */
/*   Updated: 2024/08/13 20:00:03 by maiahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_write_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->args->sync_mutex);
	if (philo->args->death_occured || philo->args->everybody_full)
	{
		pthread_mutex_unlock(&philo->args->sync_mutex);
		return (false);
	}
	printf("%ld %d %s\n", ft_now_ms() - philo->args->start_time, philo->nbr, msg);
	pthread_mutex_unlock(&philo->args->sync_mutex);
	return (true);
}

bool	ft_should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->sync_mutex);
	if (philo->args->death_occured || philo->args->everybody_full)
	{
		pthread_mutex_unlock(&philo->args->sync_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->args->sync_mutex);
	return (false);
}

bool	ft_get_forks(t_philo *philo)
{
	if (philo->args->philo_count == 1)
	{
		printf("%ld %d has taken a fork\n", ft_now_ms() - philo->args->start_time, philo->nbr);
		ft_usleep(philo->args->time2eat, philo);
		return (false);  // Single philosopher case: No forks to acquire
	}

	if (ft_should_stop(philo))
		return (false);

	pthread_mutex_lock(&philo->l_fork);
	if (!ft_write_status(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(&philo->l_fork);
		return (false);
	}

	if (ft_should_stop(philo))
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

	return (true);
}

void	ft_eat(t_philo *philo)
{
	if (!ft_write_status(philo, "is eating"))
		return;

	pthread_mutex_lock(&philo->args->sync_mutex);
	philo->meals_count++;
	philo->last_meal_beginning = ft_now_ms();
	if (philo->meals_count == philo->args->max_meals)
	{
		philo->args->total_finished++;
		if (philo->args->total_finished == philo->args->philo_count)
			philo->args->everybody_full = true;
	}
	pthread_mutex_unlock(&philo->args->sync_mutex);

	ft_usleep(philo->args->time2eat, philo);
	ft_release_forks(philo);
}

bool	ft_sleep_think(t_philo *philo)
{
	if (!ft_write_status(philo, "is sleeping"))
		return (false);

	ft_usleep(philo->args->time2sleep, philo);

	if (!ft_write_status(philo, "is thinking"))
		return (false);

	return (true);
}

void	ft_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*proutine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;

	if (philo->args->philo_count == 1)
	{
		printf("%ld %d has taken a fork\n", ft_now_ms() - philo->args->start_time, philo->nbr);
		ft_usleep(philo->args->time2eat, philo);
		return (NULL);  // Single philosopher case: No need to enter the loop
	}

	if (!(philo->nbr & 1))
		ft_usleep(100, philo);

	while (1)
	{
		if (!ft_get_forks(philo))
			break ;
		ft_eat(philo);
		if (!ft_sleep_think(philo))
			break ;
	}
	return (NULL);
}


// bool	ft_write_status(t_philo *philo, char *msg)
// {
// 	pthread_mutex_lock(&philo->args->sync_mutex);
// 	if (philo->args->death_occured || philo->args->everybody_full)
// 	{
// 		pthread_mutex_unlock(&philo->args->sync_mutex);
// 		return (false);
// 	}
// 	printf(" %ld %d %s\n", ft_now_ms() - philo->args->start_time,
// 		philo->nbr, msg);
// 	pthread_mutex_unlock(&philo->args->sync_mutex);
// 	return (true);
// }

// bool	ft_should_stop(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->args->sync_mutex);
// 	if (philo->args->death_occured || philo->args->everybody_full)
// 	{
// 		pthread_mutex_unlock(&philo->args->sync_mutex);
// 		return (true);
// 	}
// 	pthread_mutex_unlock(&philo->args->sync_mutex);
// 	return (false);
// }

// bool	ft_get_forks(t_philo *philo)
// {
// 	if (ft_should_stop(philo))
// 		return (false);
// 	pthread_mutex_lock(&philo->l_fork);
// 	if (!ft_write_status(philo, "has taken a fork"))
// 	{
// 		pthread_mutex_unlock(&philo->l_fork);
// 		return (false);
// 	}
// 	if (ft_should_stop(philo))
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

// void	ft_eat(t_philo *philo)
// {
// 	ft_write_status(philo, "is eating");
// 	pthread_mutex_lock(&philo->args->sync_mutex);
// 	philo->meals_count++;
// 	philo->last_meal_beginning = ft_now_ms();
// 	if (philo->meals_count == philo->args->max_meals)
// 	{
// 		philo->args->total_finished++;
// 		if (philo->args->total_finished == philo->args->philo_count)
// 			philo->args->everybody_full = true;
// 	}
// 	pthread_mutex_unlock(&philo->args->sync_mutex);
// 	ft_usleep(philo->args->time2eat, philo);
// 	pthread_mutex_unlock(&philo->l_fork);
// 	pthread_mutex_unlock(philo->r_fork);
// }

// bool	ft_sleep_think(t_philo *philo)
// {
// 	if (!ft_write_status(philo, "is sleeping"))
// 		return (false);
// 	ft_usleep(philo->args->time2sleep, philo);
// 	if (!ft_write_status(philo, "is thinking"))
// 		return (false);
// 	return (true);
// }

// void	ft_release_forks(t_philo *philo)
// {
// 	pthread_mutex_unlock(&philo->l_fork);
// 	pthread_mutex_unlock(philo->r_fork);
// }

// void	*proutine(void *data)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)data;
// 	if (!(philo->nbr & 1))
// 		ft_usleep(100, philo);
// 	while (1)
// 	{
// 		if (!ft_get_forks(philo))
// 			break ;
// 		ft_eat(philo);
// 		if (!ft_sleep_think(philo))
// 			break ;
// 	}
// 	return (NULL);
// }


























// void	*proutine(void *data)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)data;
// 	if (!(philo->nbr & 1))
// 		ft_usleep(100, philo);
// 	while (1)
// 	{
// 		if (!ft_get_forks(philo))
// 			break ;
// 		ft_write_status(philo, "is eating");
// 		pthread_mutex_lock(&philo->args->sync_mutex);
// 		philo->meals_count++;
// 		philo->last_meal_beginning = ft_now_ms();
// 		if (philo->meals_count == philo->args->max_meals)
// 		{
// 			philo->args->total_finished++;
// 			if (philo->args->total_finished == philo->args->philo_count)
// 				philo->args->everybody_full = true;
// 		}
// 		pthread_mutex_unlock(&philo->args->sync_mutex);
// 		ft_usleep(philo->args->time2eat, philo);
// 		pthread_mutex_unlock(&philo->l_fork);
// 		pthread_mutex_unlock(philo->r_fork);
// 		if (!ft_sleep_think(philo))
// 			break ;
// 	}
// 	return (NULL);
// }


// bool	ft_sleep_think(t_philo *philo)
// {
// 	if (!ft_write_status(philo, "is sleeping"))
// 		return (false);
// 	ft_usleep(philo->args->time2sleep);
// 	if (!ft_write_status(philo, "is thinking"))
// 		return (false);
// 	return (true);
// }


// bool	ft_get_forks(t_philo *philo)
// {
// 	if (ft_should_stop(philo))
// 		return (false);
// 	pthread_mutex_lock(&philo->l_fork);
// 	if (!ft_write_status(philo, "has taken a fork"))
// 	{
// 		pthread_mutex_unlock(&philo->l_fork);
// 		return (false);
// 	}
// 	if (ft_should_stop(philo))
// 		return (false);
// 	pthread_mutex_lock(philo->r_fork);
// 	if (!ft_write_status(philo, "has taken a fork"))
// 	{
// 		pthread_mutex_unlock(&philo->l_fork);
// 		pthread_mutex_unlock(philo->r_fork);
// 		return (false);
// 	}
// 	return (true);
// }

// void	*proutine(void *data)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)data;
// 	if (!(philo->nbr & 1))
// 		ft_usleep(100); // Small delay to avoid lock-step
// 	while (1)
// 	{
// 		if (!ft_get_forks(philo))
// 			break ;
// 		ft_write_status(philo, "is eating");
// 		pthread_mutex_lock(&philo->args->sync_mutex);
// 		philo->meals_count++;
// 		philo->last_meal_beginning = ft_now_ms();
// 		if (philo->meals_count == philo->args->max_meals)
// 		{
// 			philo->args->total_finished++;
// 			if (philo->args->total_finished == philo->args->philo_count)
// 				philo->args->everybody_full = true;
// 		}
// 		pthread_mutex_unlock(&philo->args->sync_mutex);
// 		// ft_write_status(philo, "is eating");
// 		ft_usleep(philo->args->time2eat);
// 		pthread_mutex_lock(&philo->args->sync_mutex);
// 		pthread_mutex_unlock(&philo->l_fork);
// 		pthread_mutex_unlock(philo->r_fork);
// 		pthread_mutex_unlock(&philo->args->sync_mutex);
// 		if (!ft_sleep_think(philo))
// 			break ;
// 	}
// 	return (NULL);
// }
