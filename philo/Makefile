# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keila <keila@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/30 17:22:21 by keait-he          #+#    #+#              #
#    Updated: 2025/05/21 11:11:10 by keila            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
SRC		=	src/
UTIL	=	$(SRC)utils/
SRCS	=	$(SRC)check.c $(SRC)ft_eat.c $(SRC)init.c main.c $(SRC)philosophers.c \
			$(UTIL)checkargs.c $(UTIL)ft_atoi.c $(UTIL)ft_error.c $(UTIL)utils.c  
OBJS	=	$(SRCS:.c=.o)



INCLUDE = include
INCLUDES = -I $(INCLUDE)
CFLAGS	=	-Wall -Werror -Wextra -pthread -g
CC	=	cc
AR	=	ar rcs

all:	$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
