# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikulik <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 13:34:13 by vtrofyme          #+#    #+#              #
#    Updated: 2025/07/21 19:57:27 by ikulik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD = \033[1m
RED = \033[31;2m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

NAME		= minishell

MAIN		= minishell_main.c prompter.c signals.c

BINS		= export.c unset.c exit.c env.c echo.c pwd.c cd.c builtins.c

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
TOTAL_SRCS	= $(words $(MAINSRC) $(PARSESRC) $(EXECSRC) $(UTILSRC) $(BINSRC))
SRC_NUM		= 0

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@$(MAKE) -C libft > /dev/null 2>&1
	@cc $(OBJS) $(LIBRARY) $(INCLUDES) $(MFLAGS) -o $(NAME)
	@echo

$(OBJDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	@$(eval SRC_NUM := $(shell expr $(SRC_NUM) + 1))
	@$(eval PERCENT := $(shell printf "%.0f" $(shell echo "scale=4; $(SRC_NUM) / $(TOTAL_SRCS) * 100" | bc)))
	@printf "$(BOLD)\rCompiling $(NAME): ["
	@$(eval PROGRESS := $(shell expr $(PERCENT) / 5))
	@printf "$(GREEN)%0.s#$(RESET)$(BOLD)" $(shell seq 1 $(PROGRESS))
	@if [ $(PERCENT) -lt 100 ]; then printf "%0.s-" $(shell seq 1 $(shell expr 20 - $(PROGRESS))); fi
	@printf "] "
	@if [ $(PERCENT) -eq 100 ]; then printf "$(GREEN)"; fi
	@printf "%d%% $(RESET)" $(PERCENT)
	@cc $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	$(MAKE) -C libft clean
	$(RM) $(OBJDIR)

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME)

re: fclean all
