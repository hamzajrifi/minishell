NAME = mini.a

CC = gcc

FLAG = -Wall -Wextra -Werror

HDR = 	header/minishell.h \
		header/utiles_functions.h

C_FILES =	main.c\
			functions/utiles_functions.c\
			exec/exec_cmd.c\
			exec/redirections.c\
			built_func/cd.c\
			built_func/echo.c\
			built_func/env.c\
			built_func/exit.c\
			built_func/export.c\
			built_func/pwd.c\
			built_func/unset.c\
			built_func/utils_exp.c\
			parser.c\
			utils/ft_split.c\
			utils/ft_substr.c\
			utils/all_func.c\
			exec/heredoc.c\
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
		rm -f *.o built_func/*.o
		rm -f *.o exec/*.o
		rm -f *.o utils/*.o
		rm -f $(NAME)
fclean : clean
		rm -f minishell
re : fclean all
