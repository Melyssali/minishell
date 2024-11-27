/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/24 14:40:36 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_file_access(t_minishell *minishell)
{
    int return_value;

    return_value = SUCCESS;
    if (minishell->command_line->input_file != NULL)
	    return_value = infile_access_check(minishell->command_line->input_file);
    if (minishell->command_line->output_file != NULL)
	    return_value = outfile_access_check(minishell->command_line->output_file);
    return (return_value);
}

int	infile_access_check(char *input_file)
{
	if (access(input_file, F_OK) != 0)
	{
		perror("error");
		return(FAIL);
	}
	if (access(input_file, R_OK) != 0)
	{
	    perror("Error");
        return(FAIL);
	}
    return(SUCCESS);
}

int	outfile_access_check(char *output_file)
{
    if (access(output_file, F_OK) != 0)
    {
        perror("Error");
        return(FAIL);
    }
    if (access(output_file, W_OK) != 0)
    {
        perror("Error");
        return(FAIL);
    }
    return(SUCCESS);
}
