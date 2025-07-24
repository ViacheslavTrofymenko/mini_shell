/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:59:14 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/24 17:42:53 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_from_temp_to_cmd(t_shell *shell, int index);

void	parse_cmd(t_shell *shell, int index)
{
	count_splits(shell, &(shell->cmd_p));
	cmd_split(shell, &(shell->cmd_p));
	count_sources(&(shell->cmd_p));
	alloc_source_arrays(shell, &(shell->cmd_p));
	asign_sources(shell, &(shell->cmd_p));
	create_assignments(shell, &(shell->cmd_p));
	create_args(shell, &(shell->cmd_p));
	copy_from_temp_to_cmd(shell, index);
	clean_cmd_p(&(shell->cmd_p), M_PARTIAL);
	ft_bzero(&(shell->cmd_p), sizeof(t_cmd_p));
}

void	count_sources(t_cmd_p *cmd)
{
	int	index;

	index = 0;
	while (index < cmd->num_splits)
	{
		if (ft_strncmp(cmd->splits[index], "<", 1) == 0
			&& cmd->split_qs[index][0] == Q_NORMAL)
			(cmd->num_input)++;
		if (ft_strncmp(cmd->splits[index], ">", 1) == 0
			&& cmd->split_qs[index][0] == Q_NORMAL)
			(cmd->num_output)++;
		index++;
	}
	cmd->num_files = cmd->num_input + cmd->num_output;
}

void	alloc_source_arrays(t_shell *shell, t_cmd_p *cmd)
{
	int	index;

	index = -1;
	if (cmd->num_files > 0)
	{
		cmd->f_names = malloc(cmd->num_files * sizeof(char *));
		cmd->f_mode = malloc(cmd->num_files * sizeof(char));
		cmd->rw_type = malloc (cmd->num_files * sizeof(char));
		if (cmd->f_names == NULL || cmd->f_mode == NULL
			|| cmd->rw_type == NULL)
			crit_except(shell, ER_MALLOC);
		nullify_array(cmd->f_names, cmd->num_files);
	}
	cmd->split_io = malloc(cmd->num_splits * sizeof(char));
	if (cmd->split_io == NULL)
		crit_except(shell, ER_MALLOC);
	while (++index < cmd->num_splits)
		cmd->split_io[index] = IO_KEEP;
}

void	create_args(t_shell *shell, t_cmd_p *cmd)
{
	int	index;

	index = 0;
	cmd->args = malloc((cmd->num_args + 1) * sizeof(char *));
	if (cmd->args == NULL)
		crit_except(shell, ER_MALLOC);
	nullify_array(cmd->args, cmd->num_args);
	cmd->ind_arg = 0;
	while (index < cmd->num_splits)
	{
		if (cmd->split_io[index] == IO_KEEP)
		{
			expand_dollars(shell, &(cmd->splits[index]),
				&(cmd->split_qs[index]));
			if (ft_strlen(cmd->splits[index]) == 0)
				free(cmd->splits[index]);
			else
			{
				cmd->args[cmd->ind_arg] = cmd->splits[index];
				(cmd->ind_arg)++;
			}
		}
		index++;
	}
	cmd->args[cmd->num_args] = NULL;
}

static void	copy_from_temp_to_cmd(t_shell *shell, int index)
{
	shell->cmds[index].args = shell->cmd_p.args;
	shell->cmds[index].assign = shell->cmd_p.assign;
	shell->cmds[index].f_names = shell->cmd_p.f_names;
	shell->cmds[index].f_mode = shell->cmd_p.f_mode;
	shell->cmds[index].rw_type = shell->cmd_p.rw_type;
	shell->cmds[index].num_assign = shell->cmd_p.num_assign;
	shell->cmds[index].num_args = shell->cmd_p.num_args;
	shell->cmds[index].num_input = shell->cmd_p.num_input;
	shell->cmds[index].num_output = shell->cmd_p.num_output;
	shell->cmds[index].num_files = shell->cmd_p.num_files;
	shell->cmds[index].error = shell->cmd_p.error;
	shell->cmds[index].envp = shell->envp;
	if (shell->cmd_p.error & ER_SYNTAX || (shell->cmd_p.num_splits == 0))
	{
		shell->cmds[index].error = ER_SYNTAX;
		correct_syntax_error(shell, index);
	}
}

/*
 *  FOR DEBUG PURPOSES
 * 	for(int j=0; j<shell->cmd_p.num_splits; j++)
		printf("\"%s\" ", shell->cmd_p.splits[j]);
	printf("\n");
	for(int i=0; i<shell->cmd_p.num_splits; i++)
		printf("\"%s\" ", shell->cmd_p.split_qs[i]);
	printf("\n");
	if (shell->cmds[0].er_synt_char != '\0')
		printf("Syntax error: %c\n", shell->cmds[0].er_synt_char);
 */
