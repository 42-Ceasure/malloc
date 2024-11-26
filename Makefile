
.PHONY:		all, clean, fclean, re

# test_executable
TEST		=	prog

# compiler
CC			=	clang

# flags
CFLAG		=	-Wall -Wextra -Werror -g -O0 -fsanitize=address
# CFLAG		=	-Wall -Wextra -Werror

OBJDIR		=	./obj/

# libasm
NAME		=	mymalloc
INC			=	mymalloc.h
INCDIR		=	./proj/inc/
INCFIL		=	$(addprefix $(INCDIR), $(INC))
SRCDIR		=	./proj/src/
BASESRC		=	malloc.c			free.c				realloc.c \
				dump.c				main.c
CHKDIR		= 	./proj/src/chunk/
CHKSRC		=	chunk_find.c		chunk_ask.c			chunk_edit.c \
				chunk_move_bwd.c	chunk_move_fwd.c	chunk_worm.c \
				chunk_manage.c		micro_data.c		heap.c
SRC			=	$(BASESRC) $(CHKSRC)
OBJ			=	$(SRC:.c=.o)
OBJFIL		=	$(addprefix $(OBJDIR), $(OBJ))

# test
SRCT		=	main.c
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

$(OBJDIR)%.o:	$(SRCDIR)%.c $(INCFIL)
				@mkdir -p $(OBJDIR)
				$(CC) $(CFLAG) -I $(INCDIRT) -I $(INCDIR) -o $@ -c $<

$(OBJDIR)%.o:	$(CHKDIR)%.c $(INCFIL)
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
