# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/02 16:49:32 by cel-mhan          #+#    #+#              #
#    Updated: 2022/06/02 16:49:34 by cel-mhan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= philo.c init.c utils.c error-handler.c launcher.c sleep.c eat.c

OBJS	= $(SRCS:.c=.o)

NAME	= philo

CC	= cc

FLAGS	= -Wall -Wextra -Werror 

INCLUDE	= -lpthread 

HEADER	= philo.h


all:	$(NAME)

.PHONY:	clean fclean re 

$(NAME): $(OBJS)
	$(CC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME) 

re: fclean all

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $<  -o $(<:.c=.o)
