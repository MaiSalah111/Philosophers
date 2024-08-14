/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:44:21 by maiahmed          #+#    #+#             */
/*   Updated: 2024/08/14 13:01:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILOSOPHERS 200

typedef struct s_philo
{
	int				nbr;
	time_t			last_meal_beginning;
	int				meals_count;
	pthread_t		thread;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	struct s_args	*args;
}	t_philo;

typedef struct s_args
{
	int					philo_count;
	int					time2die;
	int					time2eat;
	int					time2sleep;
	int					max_meals;
	int					total_finished;
	bool				death_occured;
	bool				everybody_full;
	time_t				start_time;
	pthread_mutex_t		sync_mutex;
	struct s_philo		philos[MAX_PHILOSOPHERS];
}	t_args;

enum e_fork
{
	LEFT,
	RIGHT
};

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
bool		ft_isint(char *str);
time_t		ft_now_ms(void);
size_t		ft_strlen(const char *str);
void		ft_usleep(time_t milli, t_philo *philo);
bool		ft_initialize_args(t_args *args, char **argv);
void		ft_initialize_philos(t_args *args);
bool		ft_break_while(t_args *args, int *i);
bool		ft_write_status(t_philo *philo, char *msg);
bool		ft_should_stop(t_philo *philo);
bool		pick_forks(t_philo *philo);
void		ft_eat(t_philo *philo);
bool		sleep_then_think(t_philo *philo);
void		release_forks(t_philo *philo);
void		*ph_routine(void	*data);

#endif