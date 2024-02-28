# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akambou <akambou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/26 20:20:59 by kmb               #+#    #+#              #
#    Updated: 2024/02/26 15:58:45 by akambou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes -g -fsanitize=address
RM = rm -rf

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))
NAME = philo
HEADER = includes/*.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) Makefile
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) > /dev/null
	@echo "✅✅$(NAME) is ready!✅✅"

obj/%.o: src/%.c
	@mkdir -p obj
	@$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	@$(RM) $(NAME) > /dev/null
	@echo "✅ Done cleaning up executables!"

clean:
	@$(RM) obj > /dev/null
	@echo "✅ Done cleaning up!"

re: fclean all

.PHONY: all clean fclean re bonus rebonus
