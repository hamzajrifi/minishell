NAME = minishell.a

CC      = gcc 

FLAGS   = -Wall -Wextra -Werror 

HDR = header/minishell.h

C_FILES =	main.c \
			minishell.c

OBJ =	main.o \
		minishell.o

all : $(NAME)

$(NAME) : 	$(HDR) $(OBJ)
			$(CC) $(FLAGS) -c $(C_FILES) 
			ar -rc $(NAME) $(OBJ)
			$(CC)   $(FLAGS) -o minishell main.c $(NAME) -lreadline

clean : 
		rm -f *.o
		rm -f $(NAME) 
fclean :  clean 
		rm -f minishell

re : fclean all 