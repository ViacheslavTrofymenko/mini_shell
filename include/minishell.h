/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:00:23 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/15 17:09:31 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
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
# define V_NFOUND -1

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
	char	**split_qs;
	char	*split_io;
	char	**args;
	char	**in_names;
	char	**out_names;
	char	*in_types;
	char	*out_types;
	int		num_output;
	int		num_input;
	int		num_args;
	char	*er_synt_char;
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
	char		**vars;
	int			size_env;
	int			size_vars;
}				t_shell;

int		ft_is_mol(char c);
int		ft_is_spec(char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_is_space(char c);
int		ft_isalnum_(int c);
void	ft_strcpy(char *dest, char *src);
// initializers and utilities
char	*safe_strdup(t_shell *shell, char *str);
void	crit_except(t_shell *data, int error_code);
void	initialize_shell(t_shell *shell, char **envp);
void	initialize_cmd_p(t_cmd_p *cmd);
void	initialize_cmd(t_cmd *cmd);
void	nullify_array(char	**arr, int size);
//parsing functions
void	get_cmd_line(t_shell *shell);
void	mark_quotes(t_shell *shell, char *str);
void	clean_cmd_p(t_cmd_p *cmd, int mode);
void	clean_cmds(t_shell *shell);
void	create_cmd_vars(t_shell *shell, char *str);
void	count_splits(t_shell *shell, t_cmd_p *cmd);
void	cmd_split(t_shell *shell, t_cmd_p *cmd);
void	count_sources(t_cmd_p *cmd);
void	asign_sources(t_shell *shell, t_cmd_p *cmd);
void	alloc_source_arrays(t_shell *shell, t_cmd_p *cmd);
void	create_args(t_shell *shell, t_cmd_p *cmd);
void	parse_cmd(t_shell *shell, int index);
void	correct_syntax_error(t_shell *shell, int index);
// execute cmds
void	execute_cmds(t_shell *shell);
//variable manipulation
int		find_var_index(char **arr, char *var, int size, int len);
void	replace_var_in_arr(t_shell *shell, char ***arr, char *var, int *size);
void	take_out_var(char **arr, char *var, int size, int len);
char	*get_var_value(char **arr, char *var, int size, int len);
void	replace_variable(t_shell *shell, char **str, char *q_str, int start);

#endif
