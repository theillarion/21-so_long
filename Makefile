NAME			=	so_long
NAME_D			=	${NAME}_debug
LIBFT_NAME		=	libft.a
LIBFT_NAME_D	=	libft_debug.a
LIBFT_NAME_S	=	ft
LIBFT_NAME_D_S	=	$(LIBFT_NAME_S)_debug
LIBFT_PATH		=	lib/libft
LIBFT			=	${LIBFT_PATH}/${LIBFT_NAME}
LIBFT_D			=	${LIBFT_PATH}/${LIBFT_NAME_D}
LIBMLX_NAME		=	libmlx.a
LIBMLX_NAME_S	=	mlx
LIBMLX_PATH		=	lib/minilibx-linux
LIBMLX			=	${LIBMLX_PATH}/${LIBMLX_NAME}
CC 				=	gcc
CC_FLAGS		=	-Wall -Werror -Wextra
CC_FLAGS_D		=	-g
HEADER			=	includes/header.h
SRCS			=	${wildcard srcs/*.c}
OBJS			=	${SRCS:%.c=%.o}
OBJS_D			=	${SRCS:%.c=%_debug.o}
INCLUDES		=	-Iincludes
RM				=	rm -rf

%.o				:	%.c
					$(CC) ${CC_FLAGS} ${INCLUDES} -c $< -o $@

%_debug.o		:	%.c
					$(CC) ${CC_FLAGS_D} ${CC_FLAGS} ${INCLUDES} -c $< -o $@

all				:	${NAME}

${NAME}			:	$(LIBMLX) $(LIBFT) $(OBJS)
					$(CC) $(INCLUDES) $(OBJS) -L${LIBFT_PATH} -l${LIBFT_NAME_S} -L${LIBMLX_PATH} -l${LIBMLX_NAME_S} -lXext -lX11 -lm -lz -o $(NAME)

debug			:	${NAME_D}

${NAME_D}		:	$(LIBMLX) $(LIBFT_D) $(OBJS_D)
					$(CC) $(INCLUDES) $(OBJS_D) -L${LIBFT_PATH} -l${LIBFT_NAME_D_S} -L${LIBMLX_PATH} -l${LIBMLX_NAME_S} -lXext -lX11 -lm -lz -o $(NAME_D)

${LIBFT}		:	
					$(MAKE) -C ${LIBFT_PATH}

${LIBFT_D}		:	
					$(MAKE) debug -C ${LIBFT_PATH}

${LIBMLX}		:	
					$(MAKE) -C ${LIBMLX_PATH}

clean			:
					$(RM) ${OBJS} $(OBJS_D)
					${MAKE} clean -C ${LIBFT_PATH}
					${MAKE} clean -C ${LIBMLX_PATH}

fclean			:	clean 
					$(RM) $(NAME) ${NAME_D}
					${MAKE} fclean -C ${LIBFT_PATH}

re				:	fclean all

.PHONY			:	all debug clean fclean re