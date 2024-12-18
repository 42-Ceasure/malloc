.PHONY:		all, clean, fclean, re

# compiler
CC			=	clang

# flags
CFLAGDEBUG	=	-Wall -Wextra -Werror -g -O0 -fsanitize=address
CFLAGBASIC	=	-Wall -Wextra -Werror

CFLAG		= 	$(CFLAGDEBUG)

OBJDIR		=	./obj/

# malloc
NAME		=	mymalloc

INCDIR		=	./inc/
INC			=	mymalloc.h
INCFIL		=	$(addprefix $(INCDIR), $(INC))

SRCDIR		=	./src/
SRC			=	allocate.c basic.c chunk.c deallocate.c heap.c large.c \
				main.c page.c reach.c size.c \


OBJ			=	$(SRC:.c=.o)
OBJFIL		=	$(addprefix $(OBJDIR), $(OBJ))

all			:	$(NAME)

$(NAME)		:	$(OBJFIL)
				@echo creating $(NAME)
				@$(CC) $(CFLAG) $^ -o $@

$(OBJDIR)%.o:	$(SRCDIR)%.c $(INCFIL)
				@mkdir -p $(OBJDIR)
				$(CC) $(CFLAG) -I $(INCDIR) -o $@ -c $<

clean		:
				rm -rf $(OBJDIR)

fclean		:			clean
				rm -rf $(NAME)
				rm -rf $(TEST)

re			:	fclean all
