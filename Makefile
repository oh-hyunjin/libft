# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 13:53:08 by hyoh              #+#    #+#              #
#    Updated: 2022/12/18 14:49:51 by hyoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

CC		=	cc
CFLAG	=	-Wall -Wextra -Werror
RM		=	rm -f

LIB_DIR	=	./lib
SRC_DIR	=	./src

SRC		=	pipex.c
OBJ		=	$(addprefix $(SRC_DIR)/, $(SRC:.c=.o))

all	: $(NAME)

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

$(NAME) : $(OBJ)
	make -C $(LIB_DIR)
	$(CC) $(CFLAG) $(OBJ) -L $(LIB_DIR) -l _ft -o $(NAME)

clean :
	make clean -C $(LIB_DIR)
	$(RM) $(OBJ)

fclean : clean
	make fclean -C $(LIB_DIR)
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus