#include "philo.h"

uint64_t	ft_now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL);
}
// Divides the sleep into smaller parts for more accuracy
void	ft_usleep(uint64_t milli)
{
	uint64_t	now;
	uint64_t	elapsed;

	now = ft_now_ms();
	elapsed = ft_now_ms();
	while (elapsed - now < milli)
	{
		usleep(333);
		elapsed = ft_now_ms();
	}
}
