/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:00:23 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/24 19:06:11 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <dirent.h>
# define BUFFER_SIZE 300
# define Q_M_CHECK 0
# define Q_M_WRITE 1
# define Q_NORMAL ' '
# define Q_SINGLE '\''
# define Q_DOUBLE '\"'
# define Q_DOLLAR '$'
# define PIPE '|'
# define Q_QUEST '?'
# define ER_MALLOC 4
# define ER_SYNTAX 2
# define ER_CMD_NOT_FOUND 127
# define ER_CMD_NOT_EXEC 126
# define IO_INPUT 8
# define IO_OUTPUT 16
# define IO_SINGLE 0
# define IO_DOUBLE 1
# define IO_REMOVE 2
# define IO_KEEP 4
# define IO_ASSIGN 8
# define M_TOTAL 1
# define M_PARTIAL 0
# define M_ADDEQUAL 1
# define M_AS_IS 0
# define V_NFOUND -1
# define C_GRN   "\001\x1B[32m\002"
# define C_BLU   "\001\x1B[34m\002"
# define C_RESET "\001\x1B[0m\002"
# define SIG_SHIFT 128

typedef struct s_one_cmd
{
	char	**envp;
	char	**args;
	char	**assign;
	char	**f_names;
	char	*f_mode;
	char	*rw_type;
	int		num_output;
	int		num_input;
	int		num_files;
	int		num_args;
	int		num_assign;
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
	char	**assign;
	char	**f_names;
	char	*f_mode;
	char	*rw_type;
	int		num_output;
	int		num_input;
	int		num_files;
	int		num_args;
	int		num_assign;
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
	char		*prompt;
	char		*cmd_line;
	int			size_env;
	int			size_vars;
	int			last_exit;
}				t_shell;

extern int		g_last_signal;

int		ft_is_mol(char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_is_space(char c);
int		ft_isalnum_(int c);
void	ft_strcpy(char *dest, char *src);
// initializers and utilities
char	*safe_strdup(t_shell *shell, char *str);
void	safe_free(char **s);
void	crit_except(t_shell *data, int error_code);
void	main_clean_exit(t_shell *shell);
void	initialize_shell(t_shell *shell, char **envp);
void	initialize_cmd_p(t_cmd_p *cmd);
void	initialize_cmd(t_cmd *cmd);
void	nullify_array(char	**arr, int size);
void	clean_double_arr(char **arr, int size);
char	**duplicate_arr(t_shell *shell, char **arr, int *new_size);
char	*safe_strjoin(t_shell *shell, char *s1, char *s2);
//parsing functions
void	get_cmd_line(t_shell *shell);
void	mark_quotes(t_shell *shell, char *str);
void	remove_quote_marks(char *str);
void	clean_cmd_p(t_cmd_p *cmd, int mode);
void	clean_cmds(t_shell *shell);
void	create_cmd_vars(t_shell *shell, char *str);
void	count_splits(t_shell *shell, t_cmd_p *cmd);
void	cmd_split(t_shell *shell, t_cmd_p *cmd);
void	count_sources(t_cmd_p *cmd);
void	asign_sources(t_shell *shell, t_cmd_p *cmd);
void	alloc_source_arrays(t_shell *shell, t_cmd_p *cmd);
void	create_assignments(t_shell *shell, t_cmd_p *cmd);
void	create_args(t_shell *shell, t_cmd_p *cmd);
void	parse_cmd(t_shell *shell, int index);
void	correct_syntax_error(t_shell *shell, int index);
int		check_syntax_except(t_shell *shell);
// execute cmds
void	execute_cmds(t_shell *shell);
void	handle_heredocs(t_shell *shell);
int		ft_error(char *str, int saved_errno);
int		ft_perror_custom(char *str, int saved_errno);
char	*ft_check_command(char **path_list, char *cmd);
void	ft_free_str_array(char **str);
char	*ft_get_path_command(t_shell *shell, int i);
void	apply_redirs(t_shell *shell, int i);
void	exec_pipe_cmds(t_shell *shell);
void	exec_or_exit(t_shell *shell, int i);

//variable manipulation
int		find_var_index(char **arr, char *var, int size, int len);
void	replace_var_in_arr(t_shell *shell, char ***arr, char *var, int *size);
void	take_out_var(char **arr, char *var, int *size, int len);
char	*get_var_value(char **arr, char *var, int size, int len);
void	expand_dollars(t_shell *shell, char **str, char **q_str);
int		check_assignment(char *arg, char *q_type);
char	*insert_str_to_str(char **str, char *ins, int start, int len);
void	transform_env(t_shell *shell, t_cmd *cmd);

//builtins
int		check_builtin(char **args);
void	run_builtin(t_shell *shell, char **args);
void	bin_export(t_shell *shell, char **args);
void	bin_unset(t_shell *shell, char **args);
void	bin_exit(t_shell *shell, char **args);
void	bin_echo(char **args);
void	bin_pwd(void);
void	bin_cd(t_shell *shell, char **args);
int		is_var_name(char *str);
void	var_name_error(t_shell *shell, char *function, char *var);
int		is_builtin_parent_only(char *cmd);

//signals
void	interactive_signal_handler(void);
void	noninteractive_signal_handler(void);
void	child_signal_handler(void);
void	sigterm_handler(void);
void	update_error_on_signal(t_shell *shell);
void	handle_ctrl_d(t_shell *shell);

#endif
