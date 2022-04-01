CC			=	gcc -g
CFLAGS		=	-Wall -Wextra -Werror
NAME 		=	minishell

LIBFT		=	libft.a
LIBFT_DIR	=	libft

SRC_DIR		=	srcs
SRC			=	srcs/minishell.c

OBJ_DIR		=	objs
OBJ			=	$(SRC: $(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all :		$(NAME)

$(NAME) :	$(LIBFT) $(OBJ)
			$(CC) $(CFLAGS) -o $@ $(OBJ)
			$(LIBFT)

$(LIBFT) :
			cd $(LIBFT_DIR); make
			cd $(LIBFT_DIR)/$(LIBFT) ./

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o $(<:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

clean :
			cd $(LIBFT_DIR); make clean
			rm -rf $(OBJ) $(OBJ_DIR)

fclean :	clean
			cd $(LIBFT_DIR); make clean
			rm -rf $(NAME) $(LIBFT)

re:			fclean all

.PHONY : 	all clean fclean