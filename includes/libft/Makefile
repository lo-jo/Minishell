# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 11:11:01 by elmaleuv          #+#    #+#              #
#    Updated: 2023/03/15 11:15:43 by ljospin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_atoi.c  ft_isalnum.c  ft_isdigit.c  ft_memchr.c  ft_memmove.c \
ft_putendl_fd.c  ft_split.c  ft_striteri.c  ft_strlcpy.c  ft_strncmp.c \
ft_strtrim.c  ft_toupper.c  ft_bzero.c  ft_isalpha.c  ft_isprint.c \
ft_memcmp.c  ft_memset.c  ft_putnbr_fd.c  ft_strchr.c  ft_strjoin.c \
ft_strlen.c  ft_strnstr.c  ft_substr.c  ft_calloc.c  ft_isascii.c  ft_itoa.c \
ft_memcpy.c  ft_putchar_fd.c  ft_putstr_fd.c  ft_strdup.c  ft_strlcat.c  ft_strmapi.c \
ft_strrchr.c  ft_tolower.c get_next_line_utils.c get_next_line.c

HEADER = libft.h

BONUS = ft_lstadd_back.c ft_lstlast.c ft_lstadd_front.c ft_lstmap.c \
ft_lstclear.c  ft_lstnew.c ft_lstdelone.c ft_lstsize.c ft_lstiter.c

BONUS_OBJS = ${BONUS:.c=.o}

OBJDIR = objs

OBJS = $(addprefix ${OBJDIR}/, ${SRCS:.c=.o})

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

NORM = norminette

RM = rm -rf

all:	${NAME}

${OBJDIR}/%.o:%.c
	@mkdir -p ${@D}
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

norminette:
	@${NORM} ${SRCS} ${BONUS} ${HEADER}

bonus: ${OBJS} ${BONUS_OBJS}
		ar rcs ${NAME} ${OBJS} ${BONUS_OBJS}

clean:
	${RM} ${OBJDIR} $(BONUS_OBJS)

fclean: clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re bonus norminette
