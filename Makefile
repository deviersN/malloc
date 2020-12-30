##
## EPITECH PROJECT, 2018
## bootstrap
## File description:
## malloc
##

CC		= gcc

RM		= rm -rf

LIB		= src/malloc.c \
		  src/malloc_extension.c \
		  src/free.c \
		  src/realloc_calloc.c \
		  src/shared_function.c \
		  src/show_alloc_mem.c

LIBNAME		= libmy_malloc.so

OBJ		= $(LIB:.c=.o)

NAME		= test

CFLAGS	= -W -Wall -Wextra -shared -fpic -I./include

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(LIBNAME) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(LIBNAME)

re:	fclean all

a:	all clean

.PHONY: all clean fclean re a
##gcc functions.c -c -Wall -Werror -fpic 
##gcc -shared -o libswag.so functions.o
##gcc -L/home/devier_n/Documents/B4-UnixSystem/PSU_2017_malloc/bootstrap/ex02/ -Wall -Werror -o test main.c -lswag
##export LD_LIBRARY_PATH=/home/devier_n/Documents/B4-UnixSystem/PSU_2017_malloc/bootstrap/ex02/
