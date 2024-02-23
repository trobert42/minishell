/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobert <trobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:59:00 by trobert           #+#    #+#             */
/*   Updated: 2022/10/29 15:34:25 by trobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_var = 0;

void	process_input(t_data *data, char *input)
{
	if (get_in_lst(data, input, data->lst) != -1 && \
	check_bonus_error(data->lst) != -1)
	{
		parse_in_block(data, data->lst);
		if (check_syntax(data, data->lst) == -1)
			hered_error(data, data->block);
		else
		{
			open_all_files(data, data->block);
			exec_one_builtin(data, *data->block, (*data->block)->cmd);
			ft_pipex(data);
			close_all_files(data->block);
		}
		free_block(data->block);
	}
	free_lst2(data->lst);
}

int	check_exit_status(t_data *data, char **input)
{
	if (g_var == CTR_C_SIGNAL)
	{
		dup2(data->saved_stdin_loop, STDIN_FILENO);
		close(data->saved_stdin_loop);
		return (1);
	}
	if (!*input)
	{
		close_all_files(data->block);
		g_var = data->last_status;
		close(data->saved_stdin_loop);
		write(STDERR_FILENO, "exit\n", 5);
		godmalloc(NULL, 0, FREE_ALL);
	}
	return (0);
}

void	loop_minishell(t_data *data)
{
	char	*input;

	input = NULL;
	while (1)
	{
		data->saved_stdin_loop = dup(STDIN_FILENO);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		data->last_status = g_var;
		g_var = 0;
		input = readline("minishell> ");
		godmalloc(input, 0, RDL);
		if (check_exit_status(data, &input))
		{
			godmalloc(input, 0, FREE_PTR);
			continue ;
		}
		process_input(data, input);
		dup2(data->saved_stdin_loop, STDIN_FILENO);
		close(data->saved_stdin_loop);
		if (input)
			add_history(input);
		godmalloc(input, 0, FREE_PTR);
	}
}

int	main(int ac, char **av, char *envp[])
{
	t_data	*data;

	(void)av;
	if (ac != 1)
		error_exit("Error nbr of args, try ./minishell", NULL);
	data = godmalloc(NULL, 0, S_DATA);
	rl_outstream = stderr;
	init_minishell(data, envp);
	maj_shlvl(&data->env_data);
	loop_minishell(data);
	return (EXIT_SUCCESS);
}
