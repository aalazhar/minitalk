# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalazhar <aalazhar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/12 16:10:36 by aalazhar          #+#    #+#              #
#    Updated: 2022/01/16 18:03:19 by aalazhar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mini_talk

C_NAME = client

S_NAME = server

SRCC = mi_client.c mi_utils.c

SRCS = mi_server.c mi_utils.c

BSRCC = bonus_client.c mi_utils.c

BSRCS = bonus_server.c mi_utils.c

BONUS = bonus

INCLD = mi_utils.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJC = $(SRCC:.c=.o)

OBJS = $(SRCS:.c=.o)

BOBJC = $(BSRCC:.c=.o)

BOBJS = $(BSRCS:.c=.o)

all: $(NAME)

$(NAME) : $(C_NAME) $(S_NAME)

$(C_NAME) : $(INCLD) $(OBJC)
	$(CC) $(CFLAGS) $(OBJC) -o $(C_NAME)

$(S_NAME) : $(INCLD) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(S_NAME)

$(BONUS): $(BOBJC) $(BOBJS) $(INCLD)
	$(CC) $(CFLAGS) $(BOBJC) -o $(C_NAME)
	$(CC) $(CFLAGS) $(BOBJS) -o $(S_NAME)

clean:
	rm -rf $(OBJC) $(OBJS) $(BOBJC) $(BOBJS)

fclean: clean
	rm -rf $(C_NAME) $(S_NAME) 

re: fclean all