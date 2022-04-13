NAME			=	so_long
NAME_D			=	${NAME}_debug

HEADER			=	includes/so_long.h
HEADER_MLX		=	includes/mlx.h
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
LIBFT_NAME_S_D	=	$(LIBFT_NAME_S)_debug
LIBFT_PATH		=	lib/libft
LIBFT			=	${LIBFT_PATH}/${LIBFT_NAME}
LIBFT_D			=	${LIBFT_PATH}/${LIBFT_NAME_D}

LIBMLX_NAME		=	libmlx.a
LIBMLX_NAME_S	=	mlx

CC_FLAGS_LINK	=	-L${LIBFT_PATH} -l${LIBFT_NAME_S} -L${LIBMLX_PATH} -l${LIBMLX_NAME_S}
CC_FLAGS_LINK_D	=	-L${LIBFT_PATH} -l${LIBFT_NAME_S_D} -L${LIBMLX_PATH} -l${LIBMLX_NAME_S}

OS				=	${shell uname -s}

ifeq (${OS},Darwin)
	LIBMLX_PATH		=	lib/minilibx-macos
	CC_FLAGS		+=	-D CURRENT_OS_MACOS
	CC_FLAGS_LINK	+=	-framework OpenGL -framework AppKit
	CC_FLAGS_LINK_D	+=	-framework OpenGL -framework AppKit
else
	LIBMLX_PATH		=	lib/minilibx-linux
	CC_FLAGS		+=	-D CURRENT_OS_LINUX
	CC_FLAGS_LINK	+=	-lXext -lX11 -lm -lz
	CC_FLAGS_LINK_D	+=	-lXext -lX11 -lm -lz
endif

LIBMLX			=	${LIBMLX_PATH}/${LIBMLX_NAME}

NOCOLOR			=	\033[0m
COLOR_LGREEN	=	\033[92m
COLOR_LYELLOW	=	\033[93m
COLOR_LCYAN		=	\033[96m
NEWLINE			=	\n

%.o				:	%.c ${HEADER}
					@${CC} ${CC_FLAGS} ${INCLUDES} -c $< -o $@
					@printf "${COLOR_LCYAN}build object${NOCOLOR} [${COLOR_LGREEN}info${NOCOLOR}]: "
					@printf "ready ${COLOR_LYELLOW}$@${NOCOLOR}${NEWLINE}"

%_debug.o		:	%.c ${HEADER}
					@${CC} ${CC_FLAGS_D} ${CC_FLAGS} ${INCLUDES} -c $< -o $@
					@printf "${COLOR_LCYAN}build object${NOCOLOR} [${COLOR_LGREEN}info${NOCOLOR}]: "
					@printf "ready ${COLOR_LYELLOW}$@${NOCOLOR}${NEWLINE}"

print-%  		: ; @echo $* = $($*)

all				:	${NAME}
debug			:	${NAME_D}

${NAME}			:	${LIBMLX} ${LIBFT} $(HEADER_MLX) ${OBJS}
					@${CC} ${INCLUDES} ${OBJS} ${CC_FLAGS_LINK} -o ${NAME}
					@printf "${COLOR_LCYAN}build${NOCOLOR} [${COLOR_LGREEN}info${NOCOLOR}]: "
					@printf "ready ${COLOR_LYELLOW}${NAME}${NOCOLOR} for ${COLOR_LYELLOW}${OS}${NOCOLOR}${NEWLINE}"

$(HEADER_MLX)	:
					cp $(LIBMLX_PATH)/$(LIBMLX_NAME_S).h $(HEADER_MLX)

${NAME_D}		:	$(LIBMLX) $(LIBFT_D) $(OBJS_D)
					@$(CC) $(INCLUDES) $(OBJS_D) ${CC_FLAGS_LINK_D} -o $(NAME_D)
					@printf "${COLOR_LCYAN}build debug${NOCOLOR} [${COLOR_LGREEN}info${NOCOLOR}]: "
					@printf "ready ${COLOR_LYELLOW}${NAME}${NOCOLOR} for ${COLOR_LYELLOW}${OS}${NOCOLOR}${NEWLINE}"

${LIBFT}		:	
					@$(MAKE) -s -C ${LIBFT_PATH}
					@printf "${COLOR_LCYAN}build ${LIBFT_NAME}${NOCOLOR} [${COLOR_LGREEN}info${NOCOLOR}]: "
					@printf "ready ${COLOR_LYELLOW}${LIBFT_NAME}${NOCOLOR}${NEWLINE}"
${LIBFT_D}		:	
					@$(MAKE) -s debug -C ${LIBFT_PATH}
					@printf "${COLOR_LCYAN}build ${LIBFT_NAME_D}${NOCOLOR} [${COLOR_LGREEN}info${NOCOLOR}]: "
					@printf "ready ${COLOR_LYELLOW}${LIBFT_NAME_D}${NOCOLOR}${NEWLINE}"

${LIBMLX}		:	
					@$(MAKE) -s -C ${LIBMLX_PATH}

clean			:
					@$(RM) ${OBJS} $(OBJS_D)
					@${MAKE} -s clean -C ${LIBFT_PATH}
					@${MAKE} -s clean -C ${LIBMLX_PATH}
					@printf "${COLOR_LCYAN}$@${NOCOLOR} [${COLOR_LGREEN}info${NOCOLOR}]: "
					@printf "ready ${COLOR_LYELLOW}${NAME}${NOCOLOR} for ${COLOR_LYELLOW}${OS}${NOCOLOR}${NEWLINE}"

fclean			:	clean 
					@$(RM) $(NAME) ${NAME_D}
					@${MAKE} -s fclean -C ${LIBFT_PATH}
					@printf "${COLOR_LCYAN}$@${NOCOLOR} [${COLOR_LGREEN}info${NOCOLOR}]: "
					@printf "ready ${COLOR_LYELLOW}${NAME}${NOCOLOR} for ${COLOR_LYELLOW}${OS}${NOCOLOR}${NEWLINE}"

re				:	fclean all
					@printf "${COLOR_LCYAN}$@${NOCOLOR} [${COLOR_LGREEN}info${NOCOLOR}]: "
					@printf "ready ${COLOR_LYELLOW}${NAME}${NOCOLOR} for ${COLOR_LYELLOW}${OS}${NOCOLOR}${NEWLINE}"

.PHONY			:	all debug clean fclean re