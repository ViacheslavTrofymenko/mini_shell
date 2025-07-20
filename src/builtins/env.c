/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 18:16:09 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/20 18:16:09 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bin_env(t_shell *shell)
{
	int	index;

	index = 0;
	while (index < shell->size_env - 1)
	{
		ft_putendl_fd(shell->envp[index], STDOUT_FILENO);
		index++;
	}
}