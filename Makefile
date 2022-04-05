NAME			=	so_long
NAME_D			=	${NAME}_debug
NAME_MAC		=	${NAME}_m
NAME_D_MAC		=	${NAME}_debug_m
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
LIBMLX_MAC_PATH	=	lib/minilibx-macos
LIBMLX			=	${LIBMLX_PATH}/${LIBMLX_NAME}
LIBMLX_MAC		=	${LIBMLX_MAC_PATH}/${LIBMLX_NAME}
CC 				=	gcc
CC_FLAGS		=	-Wall -Werror -Wextra
CC_FLAGS_D		=	-g
HEADER			=	includes/so_long.h
SRCS			=	${wildcard srcs/*.c}
OBJS			=	${SRCS:%.c=%.o}
OBJS_D			=	${SRCS:%.c=%_debug.o}
INCLUDES		=	-Iincludes
RM				=	rm -rf

%.o				:	%.c ${HEADER}
					$(CC) ${CC_FLAGS} ${INCLUDES} -c $< -o $@

%_debug.o		:	%.c ${HEADER}
					$(CC) ${CC_FLAGS_D} ${CC_FLAGS} ${INCLUDES} -c $< -o $@

all				:	${NAME}

${NAME}			:	$(LIBMLX) $(LIBFT) $(OBJS)
					$(CC) $(INCLUDES) $(OBJS) -L${LIBFT_PATH} -l${LIBFT_NAME_S} -L${LIBMLX_PATH} -l${LIBMLX_NAME_S} -lXext -lX11 -lm -lz -o $(NAME)

mac				:	${NAME_MAC}

${NAME_MAC}		:	$(LIBMLX_MAC) $(LIBFT) $(OBJS)
					$(CC) $(INCLUDES) $(OBJS) -L${LIBFT_PATH} -l${LIBFT_NAME_S} -L${LIBMLX_MAC_PATH} -l${LIBMLX_NAME_S} -framework OpenGL -framework AppKit -o $(NAME_MAC)

debug			:	${NAME_D}

${NAME_D}		:	$(LIBMLX) $(LIBFT_D) $(OBJS_D)
					$(CC) $(INCLUDES) $(OBJS_D) -L${LIBFT_PATH} -l${LIBFT_NAME_D_S} -L${LIBMLX_PATH} -l${LIBMLX_NAME_S} -lXext -lX11 -lm -lz -o $(NAME_D)

debug_mac		:	${NAME_D_MAC}

${NAME_D_MAC}	:	$(LIBMLX_MAC) $(LIBFT_D) $(OBJS_D)
					$(CC) $(INCLUDES) $(OBJS_D) -L${LIBFT_PATH} -l${LIBFT_NAME_D_S} -L${LIBMLX_MAC_PATH} -l${LIBMLX_NAME_S} -framework OpenGL -framework AppKit -o $(NAME_D_MAC)

${LIBFT}		:	
					$(MAKE) -C ${LIBFT_PATH}

${LIBFT_D}		:	
					$(MAKE) debug -C ${LIBFT_PATH}

${LIBMLX}		:	
					$(MAKE) -C ${LIBMLX_PATH}

${LIBMLX_MAC}	:	
					$(MAKE) -C ${LIBMLX_MAC_PATH}

clean			:
					$(RM) ${OBJS} $(OBJS_D)
					${MAKE} clean -C ${LIBFT_PATH}
					${MAKE} clean -C ${LIBMLX_MAC}

fclean			:	clean 
					$(RM) $(NAME) ${NAME_D}
					${MAKE} fclean -C ${LIBFT_PATH}

re				:	fclean all

.PHONY			:	all mac debug debug_mac clean fclean re