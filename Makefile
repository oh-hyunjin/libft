# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 13:53:08 by hyoh              #+#    #+#              #
#    Updated: 2022/12/29 12:05:49 by hyoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

CC		=	cc
CFLAG	=	-Wall -Wextra -Werror -fsanitize=address
RM		=	rm -f

LIB_DIR	=	./lib

SRC		=	./src/pipex.c
SRC_BN	=	./src/pipex_bonus.c
OBJ		=	$(SRC:.c=.o)
OBJ_BN	=	$(SRC_BN:.c=.o)

ifdef WITH_BONUS
	OBJECT = $(OBJ_BN)
else
	OBJECT = $(OBJ)
endif

all	: $(NAME)

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

$(NAME) : $(OBJECT)
	make -C $(LIB_DIR)
	$(CC) $(CFLAG) $(OBJECT) -L $(LIB_DIR) -l _ft -o $(NAME)

bonus :
	make WITH_BONUS=1 all

clean :
	make clean -C $(LIB_DIR)
	$(RM) $(OBJECT)

fclean : clean
	make fclean -C $(LIB_DIR)
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus