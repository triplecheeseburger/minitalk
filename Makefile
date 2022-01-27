# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 19:37:01 by hakim             #+#    #+#              #
#    Updated: 2022/01/25 10:34:16 by hakim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror 

NAME = mandatory/server \
	   mandatory/client
SRCS =	mandatory/server.c \
		mandatory/client.c
OBJS = $(SRCS:%.c=%.o)
BONUS_NAME = bonus/server \
			 bonus/client
BONUS_SRCS = bonus/server_bonus.c \
			 bonus/client_bonus.c
BONUS_OBJS = $(BONUS_SRCS:%.c=%.o)
HDR = ./includes

LIB_DIR = ./ft_printf
LIB_NAME = ftprintf
LIB = $(LIB_DIR)/lib$(LIB_NAME).a

INCLUDES = -I$(HDR) -I$(LIB_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

all: $(NAME)

bonus: $(BONUS_NAME)

mandatory/server: mandatory/server.o $(LIB)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

mandatory/client: mandatory/client.o $(LIB)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

bonus/server: bonus/server_bonus.o $(LIB)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

bonus/client: bonus/client_bonus.o $(LIB)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

$(LIB):
	make -C $(LIB_DIR)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	make -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	make -C $(LIB_DIR) fclean

re: fclean all

.PHONY: fclean all clean re bonus
