# Executable name
NAME = philo

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Sources per mode
SRC_NORMAL = main.c cycles.c philosophers_utils.c philosophers_utils_2.c time.c
OBJ_NORMAL = $(SRC_NORMAL:.c=.o)

# Default rule (normal build)
all: $(NAME)

$(NAME): $(OBJ_NORMAL)
	$(CC) $(CFLAGS) $(OBJ_NORMAL) -o $(NAME)

# Pattern rule for object files
%.o: %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object and mode markers
clean:
	rm -f $(OBJ_NORMAL)

# Full clean
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re