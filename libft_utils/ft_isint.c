
#include "philo.h"

bool	ft_isint(char *str)
{
	char	*max_int;
	size_t	str_len;

	max_int = "2147483647";
	if (*str == '+')
		str++;
	str_len = ft_strlen(str);
	if (str_len > 10)
		return (false);
	if (str_len == 10)
		while (ft_isdigit(*str) && *str <= *max_int++)
			str++;
	else
		while (ft_isdigit(*str))
			str++;
	return (!*str && true);
}
