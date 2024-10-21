/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/12 20:28:09 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	main(void)
{
	char	*input;
	

	while (1)
	{
		input = readline("minishell % ");
		if (input == NULL)
			break ;
		ft_cd(input);
		if (ft_strcmp(input, "exit") == 0)
			break ;
	}
	return (0);
}
