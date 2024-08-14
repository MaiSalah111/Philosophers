NAME := philo

CC := cc
CFLAGS := -Wall -Werror -Wextra -g

SRCS := main.c intialization.c time_utils.c ph_forks.c ph_status.c ph_routine.c helpers.c error_handler.c

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
