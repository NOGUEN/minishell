CC 				= gcc -g
RM				= rm -rf
CFLAGS 			= -Wall -Wextra -Werror
NAME 			= minishell

LIBFT		= libft.a
LIBFT_DIR	= libft

SRC_DIR 	= src
SRC 		= src/alloc_token.c \
			  src/alloc_word.c \
			  src/check.c \
			  src/get_parse_size.c \
			  src/minishell.c \
			  src/new_cmd.c \
			  src/parse.c \
			  src/quote_count.c \
			  src/signal.c \
			  src/split_cmd.c \
			  src/split_count.c \
			  src/utils.c

OBJ_DIR 	= objs
OBJ 		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all : 		$(NAME)

$(NAME) : 	$(LIBFT) $(OBJ)
			$(CC) $(CFLAGS) -o $@ $(OBJ) \
			$(LIBFT)
			

$(LIBFT) :
			cd $(LIBFT_DIR); make
			cp $(LIBFT_DIR)/$(LIBFT) ./

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			mkdir -p $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -o $(<:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

clean :
			cd $(LIBFT_DIR); make clean
			$(RM) $(OBJ) $(OBJ_DIR)

fclean : 	clean
			cd $(LIBFT_DIR); make fclean
			$(RM) $(NAME) $(LIBFT)

re : 		fclean all

.PHONY :	all clean fclean