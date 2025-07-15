/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 23:04:08 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/07/15 17:25:48 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	apply_redirs(t_cmd *cmd);
static void	exec_or_exit(t_shell *shell, int index);
static void	exec_one_cmd(t_shell *shell);
static void	exec_pipe_cmds(t_shell *shell);
int	ft_error(int num, char *str);
char	*ft_check_command(char **path_list, char *cmd);
void	ft_free_str_array(char **str);
char	*ft_get_path_command(char **cmd, char **envp);

void	handle_heredocs(t_shell *shell)
{
	int		fd;
	int		i;
	int		j;
	char	*tmp_filename;
	char	*line;

	i = 0;
	while (i < shell->num_cmds)
	{
		j = 0;
		while (j < shell->cmds[i].num_input)
		{
			if (shell->cmds[i].in_types[j] == IO_DOUBLE)
			{
				tmp_filename = ft_strjoin("/tmp/.heredoc_", shell->cmds[i].in_names[j]);
				fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (fd < 0)
					crit_except(shell, ft_error(1, tmp_filename));
				while (1)
				{
					line = readline("> ");
					if (!line || ft_strcmp(line, shell->cmds[i].in_names[j]) == 0)
						break ;
					write(fd, line, ft_strlen(line));
					write(fd, "\n", 1);
					free(line);
				}
				free(line);
				close(fd);
				free(shell->cmds[i].in_names[j]);
				shell->cmds[i].in_names[j] = tmp_filename;
			}
			j++;
		}
		i++;
	}
}

void	execute_cmds(t_shell *shell)
{
	int i;

	handle_heredocs(shell);
	if (!shell->cmds[0].args || !shell->cmds[0].args[0])
		return ;
	else if (shell->num_cmds == 1)
		exec_one_cmd(shell);
	else
		exec_pipe_cmds(shell);
}

static void	apply_redirs(t_cmd *cmd)
{
	int	i;
	int	fd;

	i = -1;
	while (++i < cmd->num_input)
	{
		if (cmd->in_types[i] == IO_SINGLE)
		{
			fd = open(cmd->in_names[i], O_RDONLY);
			if (fd < 0)
				exit(ft_error(1, cmd->in_names[i]));
			if (dup2(fd, STDIN_FILENO) < 0)
				exit(ft_error(1, "dup2 input"));
			close(fd);
		}
		else if (cmd->in_types[i] == IO_DOUBLE)
		{
			fd = open(cmd->in_names[i], O_RDONLY);
			if (fd < 0)
				exit(ft_error(1, "heredoc temp file"));
			if (dup2(fd, STDIN_FILENO) < 0)
				exit(ft_error(1, "dup2 heredoc"));
			close(fd);
			unlink(cmd->in_names[i]);
		}
	}
	i = -1;
	while (++i < cmd->num_output)
	{
		if (cmd->out_types[i] == IO_SINGLE)
			fd = open(cmd->out_names[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			fd = open(cmd->out_names[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			exit(ft_error(1, cmd->out_names[i]));
		dup2(fd, STDOUT_FILENO);
		if (dup2(fd, STDOUT_FILENO) < 0)
			exit(ft_error(1, "dup2 output"));
		close(fd);
	}
}
static void	exec_or_exit(t_shell *shell, int i)
{
	char	*path_cmd;
	t_cmd	*cmd;

	cmd = &shell->cmds[i];
	apply_redirs(cmd);
	path_cmd = ft_get_path_command(cmd->args, cmd->envp);
	if (path_cmd)
	{
		execve(path_cmd, cmd->args, cmd->envp);
		free(path_cmd);
	}
	ft_error(2, cmd->args[0]);
	crit_except(shell, 127);
}

static void	exec_one_cmd(t_shell *shell)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
		exec_or_exit(shell, 0);
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		ft_error(1, "fork");
}
static void	exec_pipe_cmds(t_shell *shell)
{
	int		i;
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	i = 0;
	prev_fd = -1;
	while (i < shell->num_cmds)
	{
		if (i < shell->num_cmds - 1 && pipe(pipe_fd) == -1)
			exit(ft_error(1, "pipe"));
		pid = fork();
		if (pid == 0)
		{
			if (i > 0)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (i < shell->num_cmds -1)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			exec_or_exit(shell, i);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (i < shell->num_cmds - 1)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		i++;
	}
	while (waitpid(-1, NULL, 0) != -1)
		continue ;
}

int	ft_error(int num, char *str)
{
	if (num == 1)
		perror(str);
	if (num == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (1);
}

char	*ft_check_command(char **path_list, char *cmd)
{
	int		i;
	char	*path_fin;
	char	*path_mid;

	i = 0;
	while (path_list[i])
	{
		path_mid = ft_strjoin(path_list[i], "/");
		path_fin = ft_strjoin(path_mid, cmd);
		free(path_mid);
		if (access(path_fin, X_OK) == 0)
			return (path_fin);
		free(path_fin);
		i++;
	}
	return (NULL);
}

void	ft_free_str_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*ft_get_path_command(char **cmd, char **envp)
{
	int		i;
	char	**path_list;
	char	*path_command;

	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
		return (NULL);
	if (ft_strchr(cmd[0], '/'))
		if (access(cmd[0], X_OK) == 0)
			return (ft_strdup(cmd[0]));
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			path_list = ft_split(envp[i] + 5, ':');
			path_command = ft_check_command(path_list, cmd[0]);
			ft_free_str_array(path_list);
			return (path_command);
		}
	}
	return (NULL);
}
