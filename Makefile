# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 13:53:08 by hyoh              #+#    #+#              #
#    Updated: 2023/01/08 14:14:04 by hyoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

CC		=	cc
CFLAG	=	-Wall -Wextra -Werror
RM		=	rm -f

LIB_DIR	=	./lib
SRCS_DIR	=	./src

SRC		=	pipex.c pipex_utils.c ready_for_exe.c
SRC_BN	=	pipex_bonus.c pipex_utils_bonus.c ready_for_exe_bonus.c

OBJ		=	$(addprefix $(SRCS_DIR)/, $(SRC:.c=.o))
OBJ_BN	=	$(addprefix $(SRCS_DIR)/, $(SRC_BN:.c=.o))

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
	$(RM) $(OBJ) $(OBJ_BN)

fclean : clean
	make fclean -C $(LIB_DIR)
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re bonus