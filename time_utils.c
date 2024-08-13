/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maiahmed <maiahmed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:49:46 by maiahmed          #+#    #+#             */
/*   Updated: 2024/08/13 17:33:04 by maiahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	ft_now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL);
}

void	ft_usleep(time_t milli, t_philo *philo)
{
	time_t	now;
	time_t	elapsed;

	now = ft_now_ms();
	elapsed = ft_now_ms();
	while (elapsed - now < milli)
	{
		if (ft_should_stop(philo))
			return ;
		usleep(300);
		elapsed = ft_now_ms();
	}
}

// void	ft_usleep(time_t milli)
// {
// 	time_t	now;
// 	time_t	elapsed;

// 	now = ft_now_ms();
// 	elapsed = ft_now_ms();
// 	while (elapsed - now < milli)
// 	{
// 		if (ft_should_stop(philo))
// 			return ;
// 		usleep(300);  // Small sleep intervals to reduce CPU usage
// 		elapsed = ft_now_ms();
// 	}
// }
