HEADER_DIR = ./includes

HEADER = ${HEADER_DIR}/minishell.h

LIBFT_DIR =	./includes/libft

LIBFT =	$(LIBFT_DIR)/libft.a

SRCS_DIR = ./srcs

PARSING_DIR = ${SRCS_DIR}/parser

CMD_DIR = ${SRCS_DIR}/cmd

RED_DIR = ${SRCS_DIR}/redir

SIG_DIR = ${SRCS_DIR}/signal

CORE_DIR = ${SRCS_DIR}/shell

EXEC_DIR = ${SRCS_DIR}/exec

BLT_DIR = ${SRCS_DIR}/builtins

EXP_DIR = ${SRCS_DIR}/expansion

FD_DIR = ${SRCS_DIR}/fd

HASH_DIR = ${SRCS_DIR}/hash

UTILS_DIR = ${SRCS_DIR}/utils

SRCS =		${SRCS_DIR}/main.c \
			${CMD_DIR}/prep_command.c \
			${CMD_DIR}/parse_cmd.c \
			${CMD_DIR}/parse_redir.c \
			${CMD_DIR}/cmd_utils.c \
			${RED_DIR}/redir_in.c \
			${RED_DIR}/redir_out.c \
			${RED_DIR}/heredoc_redir.c \
			${PARSING_DIR}/char_validation.c \
			${PARSING_DIR}/token_list_utils.c \
			${PARSING_DIR}/tokenizer.c \
			${PARSING_DIR}/syntax.c \
			${PARSING_DIR}/trimmer.c \
			${SIG_DIR}/signal.c \
			${CORE_DIR}/core.c \
			${CORE_DIR}/clear_free.c \
			${CORE_DIR}/error.c \
			${EXP_DIR}/expander.c \
			${EXP_DIR}/quotes.c \
			${EXP_DIR}/dollar_exp.c \
			${EXP_DIR}/expansion_utils.c \
			${EXP_DIR}/list_utils.c \
			${BLT_DIR}/pwd.c \
			${BLT_DIR}/echo.c \
			${BLT_DIR}/env.c \
			${BLT_DIR}/unset.c \
			${BLT_DIR}/export.c \
			${BLT_DIR}/cd.c \
			${BLT_DIR}/cd_utils.c \
			${BLT_DIR}/exit.c \
			${EXEC_DIR}/exec_cmd.c \
			${EXEC_DIR}/path.c \
			${EXEC_DIR}/path_utils.c \
			${EXEC_DIR}/pipe_exec.c \
			${EXEC_DIR}/post_processing.c \
			${EXEC_DIR}/prep_exec.c \
			${FD_DIR}/fd.c \
			${HASH_DIR}/hash_init.c \
			${HASH_DIR}/hash_function.c \
			${HASH_DIR}/hash_hunt.c \
			${HASH_DIR}/hash_utils.c \
			${HASH_DIR}/hash_free.c \
			${HASH_DIR}/env_to_hash.c \

OBJDIR = objs

OBJS = $(addprefix ${OBJDIR}/, ${SRCS:.c=.o})

NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3

LFLAGS=  -lreadline

NORM = norminette

RM = rm -rf

${OBJDIR}/%.o:%.c
	@mkdir -p ${@D}
	${CC} ${CFLAGS} -c $< -o $@

all:			${NAME}

${NAME}:		${LIBFT} ${OBJS}
				${CC} ${CFLAGS} ${OBJS} ${LFLAGS} ${LIBFT} -o ${NAME}

${LIBFT}:
				make bonus -C ${LIBFT_DIR}
clean:
			make -C ${LIBFT_DIR} clean
			${RM} ${OBJS} ${OBJDIR}

fclean:		clean
			make -C ${LIBFT_DIR} fclean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
