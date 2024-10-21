/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/12 21:01:55 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// t_tree *create_node(int type)
// {
// 	t_tree *node = (t_tree*)malloc(sizeof(t_tree));
// 	node->type = type;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }
// // wc -l < Makefile | grep "test"

// void    split_into_tokens(char *s)
// {
// 	char *ptr;
// 	int how_many;

// 	ptr = s;
// 	while (*s)
// 	{
// 		if (is_operator(*s++) != NULL)
// 		{
// 			how_many = s - ptr;
// 			//do something
// 		}
// 		s++;
// 	}
// }

// int is_operator(char c)
// {
// 	if (c == '>')
// 		return(LREDIRECTION);
// 	else if (c == '>>')
// 		return(APPEND);
// 	else if (c == '<')
// 		return(RREDIRECTION);
// 	else if (c == '|')
// 		return(PIPE);
// 	else 
// 		return(0);
// }