NAME = mini.a

CC = gcc

FLAG = -Wall -Wextra -Werror

HDR = 	header/minishell.h \
		header/utiles_functions.h

C_FILES =	main.c\
			functions/utiles_functions.c\
			mini.c

OBJ = $(C_FILES:.c=.o)
# main.o\
# 		functions/utiles_functions.o\
# 		mini.o


all : $(NAME)

$(NAME) : $(HDR) $(OBJ)
			$(CC) $(FLAG) -c $(C_FILES)
			ar -rc $(NAME) $(OBJ)
			$(CC) $(FLAG) -o minishell main.c -lreadline $(NAME)

clean :	
		rm -f *.o functions/*.o
		rm -f $(NAME)
fclean : clean
		rm -f minishell
re : fclean all
