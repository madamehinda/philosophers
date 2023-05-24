# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hferjani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 09:10:43 by hferjani          #+#    #+#              #
#    Updated: 2023/04/11 12:03:05 by hferjani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS	= main.c \
		init.c \
		utils.c \
		threads.c\
		routine.c \
		think_sleep_or_just_die.c \
		monitor.c 

OBJS	= $(SRCS:.c=.o)

NAME	= philo

CLANG	= gcc

FLAGS	= -Wall -Wextra -Werror

INCLUDE	= -pthread

HEADER	= philo.h

all:	$(NAME)

.PHONY:	clean fclean re bonus 

$(NAME): $(OBJS)
	$(CLANG) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

%.o: %.c $(HEADER)
	$(CLANG) $(FLAGS) -c $<  -o $(<:.c=.o)















