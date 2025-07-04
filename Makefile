NAME = minishell

SRC 		= minishell_main.c

SRCSDIR		= src
OBJDIR		= obj
INCLUDE		= include

SRCS		= $(addprefix $(SRCSDIR)/, $(SRC))

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

CFLAGS = -Wall -Wextra -Werror -g
MFLAGS = -lreadline

RM = rm -f

all: $(NAME)

$(NAME): $(LIBRARY) $(OBJDIR) $(OBJS)
	cc $(OBJS) $(LIBRARY) -o $(NAME) $(MFLAGS)

$(BONUSNAME): $(BONUSOBJS) $(LIBRARY)
	cc $(BONUSOBJS) $(LIBRARY) -o $(BONUSNAME)

$(OBJDIR)/%.o: $(SRCSDIR)/%.c
	cc $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJS) $(BONUSOBJS)

fclean: clean
	$(RM) $(NAME) $(BONUSNAME)

re: fclean all
