
.PHONY:		all, clean, fclean, re

# test_executable
TEST		=	prog

# compiler
CC			=	clang

# flags
CFLAG		=	-Wall -Wextra -Werror

OBJDIR		=	./obj/

# libasm
NAME		=	mymalloc
SRC			=	malloc.c			free.c				heap.c \
				chunk_find.c		chunk_ask.c			chunk_edit.c \
				chunk_move_bwd.c	chunk_move_fwd.c \
				main.c
OBJ			=	$(SRC:.c=.o)
SRCDIR		=	./proj/src/
INCDIR		=	./proj/inc/
OBJFIL		=	$(addprefix $(OBJDIR), $(OBJ))

# test
SRCT		=	main.c _len.c _cpy.c _cmp.c _write.c _read.c _dup.c
OBJT		=	$(SRCT:.c=.o)
SRCDIRT		=	./test/src/
INCDIRT		=	./test/inc/
OBJFILT		=	$(addprefix $(OBJDIR), $(OBJT))

all			:	$(NAME)

test		:	$(NAME) $(TEST)

$(NAME)		:	$(OBJFIL)
				@echo creating $(NAME)
				@$(CC) $(CFLAG) $^ -o $@

$(TEST)		:	$(OBJFILT) $(NAME)
				@echo creating $(TEST)
				@$(CC) $(CFLAG) $^ -o $@

$(OBJDIR)%.o:	$(SRCDIR)%.c
				@mkdir -p $(OBJDIR)
				$(CC) $(CFLAG) -I $(INCDIRT) -I $(INCDIR) -o $@ -c $<

$(OBJDIR)%.o:	$(SRCDIRT)%.c
				@mkdir -p $(OBJDIR)
				$(CC) $(CFLAG) -I $(INCDIRT) -I $(INCDIR) -o $@ -c $<

clean		:
				rm -rf $(OBJDIR)

fclean		:			clean
				rm -rf $(NAME)
				rm -rf $(TEST)

re			:	fclean all
