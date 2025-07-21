# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 13:34:13 by vtrofyme          #+#    #+#              #
#    Updated: 2025/07/21 14:25:46 by vtrofyme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

MAIN		= minishell_main.c prompter.c

BINS		= export.c unset.c exit.c env.c echo.c

UTIL		= basics_simple.c initializer.c cleaners.c exceptors.c\
			basics_advanced.c variable_manipulations.c

EXEC		= execute.c execute_utils.c handle_heredocs.c apply_redirections.c\
			exec_pipe_cmds.c error_msg.c

PARSE		= handle_assignments.c parse_dollar_utils.c parse_quotes.c\
			parse_cmd.c parse_stream_names.c parse_pipes.c parse_split_cmd.c\
			parse_dollar.c

PARSEDIR	= src/parse
EXECDIR		= src/execute
UTILDIR		= src/utils
MAINDIR		= src/main
BINSDIR		= src/builtins
MAINSRC		= $(addprefix $(MAINDIR)/, $(MAIN))
BINSRC		= $(addprefix $(BINSDIR)/, $(BINS))
UTILSRC		= $(addprefix $(UTILDIR)/, $(UTIL))
EXECSRC		= $(addprefix $(EXECDIR)/, $(EXEC))
PARSESRC	= $(addprefix $(PARSEDIR)/, $(PARSE))
SRCSDIR		= src
OBJDIR		= obj
INCLUDE		= include

SRCS		= $(MAINSRC) $(PARSESRC) $(EXECSRC) $(UTILSRC) $(BINSRC)

OBJS		= $(SRCS:src/%.c=obj/%.o)

CFLAGS		= -Wall -Wextra -Werror -g3
MFLAGS		= -lreadline -L libft -lft
INCLUDES	= -I$(INCLUDE)

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	$(MAKE) -C libft
	cc $(OBJS) $(LIBRARY) $(INCLUDES) $(MFLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	cc $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	$(MAKE) -C libft clean
	$(RM) $(OBJDIR)

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME)

re: fclean all
