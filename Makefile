CC 				= gcc -g -fsanitize=address
RM				= rm -rf
CFLAGS 			= -Wall -Wextra -Werror
NAME 			= minishell

LIBFT		= libft.a
LIBFT_DIR	= libft

#READLINE_LIB 	= -lreadline -L/usr/local/opt/readline/lib
#READLINE_INC	= -I/usr/local/opt/readline/include

READLINE_LIB 	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
READLINE_INC	= -I /Users/$(USER)/.brew/opt/readline/include

#READLINE_LIB	= -lreadline -L/opt/homebrew/opt/readline/lib
#READLINE_INC	= -I/opt/homebrew/opt/readline/include

SRC_DIR 	= src
SRC 		= src/parse/alloc_token.c \
			  src/parse/alloc_word.c \
			  src/parse/check.c \
			  src/parse/get_env.c \
			  src/parse/get_parse_size.c \
			  src/parse/new_cmd.c \
			  src/parse/parse.c \
			  src/parse/quote_count.c \
			  src/parse/split_cmd.c \
			  src/parse/split_count.c \
			  src/parse/utils.c		\
			  src/built_in/unset.c		\
			  src/built_in/exit.c		\
			  src/built_in/export.c		\
			  src/built_in/export_utils.c		\
			  src/built_in/env.c		\
			  src/built_in/cd.c		\
			  src/minishell.c \
			  src/signal.c \
			  src/exec.c		\
			  src/cmd_info.c		\
			  src/utils/util1.c	\
			  src/utils/util2.c	\
			  src/get_next_line/get_next_line.c\
			  src/get_next_line/get_next_line_utils.c

OBJ_DIR 	= objs
OBJ 		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all : 		$(NAME)

$(NAME) : 	$(LIBFT) $(OBJ)
			$(CC) -o $@ $(OBJ) $(READLINE_LIB) $(READLINE_INC)\
			$(LIBFT)
			

$(LIBFT) :
			cd $(LIBFT_DIR); make
			cp $(LIBFT_DIR)/$(LIBFT) ./

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			mkdir -p $(OBJ_DIR)/built_in
			mkdir -p $(OBJ_DIR)/parse
			mkdir -p $(OBJ_DIR)/utils
			mkdir -p $(OBJ_DIR)/get_next_line
			$(CC) -c $< -o $(<:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) \
			$(READLINE_INC)

clean :
			cd $(LIBFT_DIR); make clean
			$(RM) $(OBJ) $(OBJ_DIR)

fclean : 	clean
			cd $(LIBFT_DIR); make fclean
			$(RM) $(NAME) $(LIBFT)

re : 		fclean all

.PHONY :	all clean fclean
