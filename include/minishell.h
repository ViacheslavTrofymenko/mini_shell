/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:00:23 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/14 13:43:15 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
# define Q_M_CHECK 0
# define Q_M_WRITE 1
# define Q_NORMAL ' '
# define Q_SINGLE '\''
# define Q_DOUBLE '\"'
# define Q_DOLLAR '$'
# define PIPE '|'
# define ER_MALLOC 2
# define ER_SYNTAX 4
# define IO_SINGLE 0
# define IO_DOUBLE 1
# define IO_REMOVE 1
# define IO_KEEP 0
# define M_TOTAL 1
# define M_PARTIAL 0

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_one_cmd
{
	char	*cmd_path;
	char	**envp;
	char	**args;
	char	**in_names;
	char	**out_names;
	char	*in_types;
	char	*out_types;
	int		num_output;
	int		num_input;
	int		num_args;
	char	er_synt_char;
	int		error;
}			t_cmd;

typedef struct s_cmd_parser
{
	char	*line;
	char	*q_type;
	char	**splits;
	char	*split_type;
	char	*split_io;
	char	**args;
	char	**in_names;
	char	**out_names;
	char	*in_types;
	char	*out_types;
	int		num_output;
	int		num_input;
	int		num_args;
	char	er_synt_char;
	int		num_splits;
	int		ind_arg;
	int		ind_start;
	int		len;
	int		error;
}			t_cmd_p;

typedef struct s_quote_parser
{
	int		q_flag;
	int		ind_strt;
	int		ind_line;
	char	*str;
	char	*q_marker_str;
}			t_qoutes;

typedef struct s_shell_metadata
{
	t_cmd		*cmds;
	t_qoutes	qts;
	t_cmd_p		cmd_p;
	int			num_cmds;
	char		**envp;
}				t_shell;

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_memset(void *s, char c, size_t n);
size_t	ft_strlen(const char *s);
int		ft_is_space(char c);
int		ft_isdigit(int c);
int		ft_isalnum_(int c);
void	ft_intset(int	*arr, int c, int n);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
void	get_cmd_line(t_shell *shell);
void	mark_quotes(t_shell *shell, char *str);
void	crit_except(t_shell *data, int error_code);
void	initialize_shell(t_shell *shell, char **envp);
void	initialize_cmd_p(t_cmd_p *cmd);
void	initialize_cmd(t_cmd *cmd);
void	clean_cmd_p(t_cmd_p *cmd, int mode);
void	clean_cmds(t_shell *shell);
void	nullify_array(char	**arr, int size);
void	create_cmd_vars(t_shell *shell, char *str);
void	count_splits(t_shell *shell, t_cmd_p *cmd);
void	cmd_split(t_shell *shell, t_cmd_p *cmd);
void	count_sources(t_cmd_p *cmd);
void	asign_sources(t_shell *shell, t_cmd_p *cmd);
void	alloc_source_arrays(t_shell *shell, t_cmd_p *cmd);
void	create_args(t_shell *shell, t_cmd_p *cmd);
void	parse_cmd(t_shell *shell, int index);
// execute cmds
void	execute_cmds(t_shell *shell);

#endif
