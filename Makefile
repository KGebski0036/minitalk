# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 11:19:49 by kgebski           #+#    #+#              #
#    Updated: 2023/06/03 20:07:28 by kgebski          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror -O3
LPATH = ./libft

all: libft server client

server: server.c
	gcc $(CFLAGS) server.c $(LPATH)/libft.a -o server

client: client.c
	gcc $(CFLAGS) client.c $(LPATH)/libft.a -o client

clean:
	make -C $(LPATH) clean
	
fclean: 
	$(RM) server
	$(RM) client
	make -C $(LPATH) fclean

re: fclean all

libft:
	make -C $(LPATH)

.PHONY: all clean fclean re libft