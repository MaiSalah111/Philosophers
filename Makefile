NAME := philo

CC := cc
CFLAGS := -Wall -Werror -Wextra -g

SRCS := main.c init_args.c init_philos.c time_utils.c ph_utils.c helpers/ft_atoi.c helpers/ft_isdigit.c helpers/ft_isint.c helpers/ft_strlen.c 		

OBJS := $(SRCS:.c=.o)

%.o: %.c
	@$(CC) -g $(CFLAGS) -c $< -o $@ -I./

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -pthread

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
