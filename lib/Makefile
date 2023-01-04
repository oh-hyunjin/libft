# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/18 14:20:55 by hyoh              #+#    #+#              #
#    Updated: 2023/01/02 12:27:52 by hyoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	lib_ft.a

CC					=	cc
CFLAG				=	-Wall -Wextra -Werror
RM					=	rm -f
AR					=	ar -crs

LIBFT_DIR			=	./libft
FT_PRINTF_DIR		=	./ft_printf
GET_NEXT_LINE_DIR	=	./get_next_line

LIBFT_SRC			=	ft_isalpha.c \
						ft_isdigit.c \
						ft_isalnum.c \
						ft_isascii.c \
						ft_isprint.c \
						ft_strlen.c \
						ft_memset.c \
						ft_bzero.c \
						ft_memcpy.c \
						ft_memmove.c \
						ft_strlcpy.c \
						ft_strlcat.c \
						ft_toupper.c \
						ft_tolower.c \
						ft_strchr.c \
						ft_strrchr.c \
						ft_strncmp.c \
						ft_memcmp.c \
						ft_memchr.c \
						ft_strnstr.c \
						ft_atoi.c \
						ft_calloc.c \
						ft_strdup.c \
						ft_substr.c \
						ft_strjoin.c \
						ft_strtrim.c \
						ft_split.c \
						ft_itoa.c \
						ft_strmapi.c \
						ft_striteri.c \
						ft_putchar_fd.c \
						ft_putstr_fd.c \
						ft_putendl_fd.c \
						ft_putnbr_fd.c

GET_NEXT_LINE_SRC	=	get_next_line.c \
						get_next_line_utils.c \

LIBFT_OBJ			=	$(addprefix $(LIBFT_DIR)/, $(LIBFT_SRC:.c=.o))
GET_NEXT_LINE_OBJ	=	$(addprefix $(GET_NEXT_LINE_DIR)/, $(GET_NEXT_LINE_SRC:.c=.o))

all : $(NAME)

$(NAME) : $(LIBFT_OBJ) $(GET_NEXT_LINE_OBJ)

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@
	$(AR) $(NAME) $@

clean :
	$(RM) $(LIBFT_OBJ)
	$(RM) $(GET_NEXT_LINE_OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re libft get_next_line