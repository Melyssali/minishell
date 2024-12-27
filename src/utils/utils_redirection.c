/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/26 21:26:48 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

static void	count_redirections(t_data *data, char **arr, char redir_sign)
{
	int	i;

	i = 0;
	data->arr_redir_size = 0;
	while (arr[i] && arr[i][0] != '|')
	{
		if (arr[i][0] == redir_sign && arr[i][1] == '\0')
			data->arr_redir_size++;
		else if (data->operator_type == APPEND_OUTPUT
				&& arr[i][1] == redir_sign)
			data->arr_redir_size++;
		arr++;
	}
}

char	**malloc_array(t_data *data, char **cpy_arr, char redir_sign)
{
	
	char	**arr;

	count_redirections(data, cpy_arr, redir_sign);
	arr = malloc(sizeof(char *) * (data->arr_redir_size + 1));
	arr[data->arr_redir_size] = NULL;
	return (arr);
}