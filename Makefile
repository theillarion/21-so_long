NAME			=	so_long
NAME_D			=	${NAME}_debug

HEADER			=	includes/so_long.h
SRCS			=	${wildcard srcs/*.c}
OBJS			=	${SRCS:%.c=%.o}
OBJS_D			=	${SRCS:%.c=%_debug.o}

CC 				=	gcc
CC_FLAGS		=	-Wall -Werror -Wextra
CC_FLAGS_D		=	-g

INCLUDES		=	-Iincludes
RM				=	rm -rf

LIBFT_NAME		=	libft.a
LIBFT_NAME_D	=	libft_debug.a
LIBFT_NAME_S	=	ft
LIBFT_NAME_D_S	=	$(LIBFT_NAME_S)_debug
LIBFT_PATH		=	lib/libft
LIBFT			=	${LIBFT_PATH}/${LIBFT_NAME}
LIBFT_D			=	${LIBFT_PATH}/${LIBFT_NAME_D}

LIBMLX_NAME		=	libmlx.a
LIBMLX_NAME_S	=	mlx

CC_FLAGS_LINK	=	-L${LIBFT_PATH} -l${LIBFT_NAME_S} -L${LIBMLX_PATH} -l${LIBMLX_NAME_S}

OS				=	${shell uname -s}

ifeq (${OS},Mac)
	LIBMLX_PATH		=	lib/minilibx-macos
	CC_FLAGS_LINK	+=	-framework OpenGL -framework AppKit
else
	LIBMLX_PATH		=	lib/minilibx-linux
	CC_FLAGS_LINK	+=	-lXext -lX11 -lm -lz
	CC_FLAGS_LINK	+=	-D CURRENT_OS=LINUX

endif

LIBMLX			=	${LIBMLX_PATH}/${LIBMLX_NAME}

NOCOLOR			=	\033[0m
COLOR_LGREEN	=	\033[92m
COLOR_LYELLOW	=	\033[93m
COLOR_LCYAN		=	\033[96m
NEWLINE			=	\n

%.o				:	%.c ${HEADER}
					@${CC} ${CC_FLAGS} ${INCLUDES} -c $< -o $@

%_debug.o		:	%.c ${HEADER}
					${CC} ${CC_FLAGS_D} ${CC_FLAGS} ${INCLUDES} -c $< -o $@

print-%  		: ; @echo $* = $($*)

all				:	${NAME}
debug			:	${NAME_D}

${NAME}			:	${LIBMLX} ${LIBFT} ${OBJS}
					@${CC} ${INCLUDES} ${OBJS} ${CC_FLAGS_LINK} -o ${NAME}
					@printf "${COLOR_LCYAN}build${NOCOLOR} [${COLOR_LGREEN}info${NOCOLOR}]: "
					@printf "Complete ${COLOR_LYELLOW}${NAME}${NOCOLOR} for ${COLOR_LYELLOW}${OS}${NOCOLOR}${NEWLINE}"

print_build			:	
					@printf "${COLOR_LGREEN}Build ${COLOR_LYELLOW}${NAME}${COLOR_LGREEN} for ${COLOR_LYELLOW}${OS}${NEWLINE}$(NOCOLOR)"

${NAME_D}		:	$(LIBMLX) $(LIBFT_D) $(OBJS_D)
					$(CC) $(INCLUDES) $(OBJS_D) ${CC_FLAGS_LINK} -o $(NAME_D)
					@printf "${COLOR_LCYAN}build debug${NOCOLOR} [${COLOR_LGREEN}info${NOCOLOR}]: "
					@printf "Complete ${COLOR_LYELLOW}${NAME}${NOCOLOR} for ${COLOR_LYELLOW}${OS}${NOCOLOR}${NEWLINE}"

${LIBFT}		:	
					@$(MAKE) -s -C ${LIBFT_PATH}

${LIBFT_D}		:	
					@$(MAKE) -s debug -C ${LIBFT_PATH}

${LIBMLX}		:	
					@$(MAKE) -s -C ${LIBMLX_PATH}

clean			:
					@$(RM) ${OBJS} $(OBJS_D)
					@${MAKE} -s clean -C ${LIBFT_PATH}
					@${MAKE} -s clean -C ${LIBMLX_PATH}
					@printf "${COLOR_LCYAN}$@${NOCOLOR} [${COLOR_LGREEN}info${NOCOLOR}]: "
					@printf "Complete ${COLOR_LYELLOW}${NAME}${NOCOLOR} for ${COLOR_LYELLOW}${OS}${NOCOLOR}${NEWLINE}"

fclean			:	clean 
					@$(RM) $(NAME) ${NAME_D}
					@${MAKE} -s fclean -C ${LIBFT_PATH}
					@printf "${COLOR_LCYAN}$@${NOCOLOR} [${COLOR_LGREEN}info${NOCOLOR}]: "
					@printf "Complete ${COLOR_LYELLOW}${NAME}${NOCOLOR} for ${COLOR_LYELLOW}${OS}${NOCOLOR}${NEWLINE}"

re				:	fclean all
					@printf "${COLOR_LCYAN}$@${NOCOLOR} [${COLOR_LGREEN}info${NOCOLOR}]: "
					@printf "Complete ${COLOR_LYELLOW}${NAME}${NOCOLOR} for ${COLOR_LYELLOW}${OS}${NOCOLOR}${NEWLINE}"

.PHONY			:	all debug clean fclean re