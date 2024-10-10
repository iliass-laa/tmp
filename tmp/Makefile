CFILES = sources/one.c sources/two.c sources/three.c\
			sources/constractors.c sources/parse.c \
			sources/print.c sources/tree.c sources/exec.c\
			sources/freedom.c sources/tokens.c sources/ordering.c\
			sources/exec_new.c  sources/builtins/env.c sources/builtins/lstoarry.c \
			sources/pipe.c sources/del.c


MINISHELL_ART = \
"\033[32m\n"\
"███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████ ╗██╗  ██╗ ███████╗ ██╗      ██╗     \n"\
"████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════ ╝██║  ██║ ██╔════╝ ██║      ██║     \n"\
"██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████ ╗███████║ █████╗   ██║      ██║     \n"\
"██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██ ║██╔══██║ ██╔══╝   ██║      ██║     \n"\
"██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████ ║██║  ██║ ███████╗ ███████╗ ███████╗\n"\
"╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════ ╝╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝\n"\
"						      By: TILLAS & NolYel  \033[0m"

RLFLAGS =	-L/Users/ilaasri/.brew/opt/readline/lib -lreadline # tell linker where to look for libs , libs to link 
RLINCLUDE	=	-I/Users/ilaasri/.brew/opt/readline/include  # tell compiler where to find headers

CC = cc
OBJ = $(CFILES:.c=.o)
NAME = minishell
My_lib = libft/libft.a

all : ascii_art $(My_lib) $(NAME)

%.o : %.c Makfile
	$(CC) $(CFLAGS) -c $(RLINCLUDE) $< -o $@

$(My_lib) : 
	make -C libft

$(NAME) : $(OBJ) $(My_lib)
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r \033[0m" $@
	$(CC) $^ $(CFLAGS) $(My_lib) $(RLFLAGS) -o $@

clean :
	@make clean -C libft
	rm -rf $(OBJ)

ascii_art :
	@echo $(MINISHELL_ART)

fclean : clean
	@make fclean -C libft
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re