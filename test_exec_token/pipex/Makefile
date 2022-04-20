
NAME = pipex



# Files

EXT_LIB = libft.a

LIB_PATH = ./includes/libft/

SRC = ./srcs/main.c									\
	  ./srcs/inout.c								\
	  ./srcs/exec.c									\
	  ./srcs/parse.c								\
	  ./srcs/get_next_line/get_next_line.c			\
	  ./srcs/get_next_line/get_next_line_utils.c	\
	  ./srcs/utils/util1.c							\
	  ./srcs/utils/util2.c							\

OBJ = $(SRC:.c=.o)



# Compile

CC = gcc

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

all : $(NAME)

$(NAME) : libft $(OBJ)
		$(CC) $(CFLAGS) $(LIB_PATH)$(EXT_LIB) $(OBJ) -o $(NAME)



# Clean, Re

RM : rm -f

clean : clean_libft
		$(RM) $(OBJ)

fclean : clean fclean_libft
		$(RM) $(NAME)

re : fclean all




############### External library #################

libft :
		$(MAKE) -C $(LIB_PATH) all

clean_libft :
		$(MAKE) -C $(LIB_PATH) clean

fclean_libft :
		$(MAKE) -C $(LIB_PATH) fclean
