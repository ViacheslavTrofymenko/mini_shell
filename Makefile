# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 13:34:13 by vtrofyme          #+#    #+#              #
#    Updated: 2025/07/04 13:58:11 by vtrofyme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell

SRC 		= minishell_main.c

SRCSDIR		= src
OBJDIR		= obj
INCLUDE		= include

SRCS		= $(addprefix $(SRCSDIR)/, $(SRC))

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))

CFLAGS		= -Wall -Wextra -Werror -g

INCLUDES	= -I$(INCLUDE)

RM = rm -f

all: $(NAME)

$(NAME): $(LIBRARY) $(OBJDIR) $(OBJS)
	cc $(OBJS) $(LIBRARY) $(INCLUDES) -lreadline -o $(NAME)

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
