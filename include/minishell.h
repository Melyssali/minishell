/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/17 21:37:02 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define ERROR -1

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_parser_data
{
	char **token_array;

}			t_parser_data;

// typedef enum {
// 	RREDIRECTION,
// 	LREDIRECTION,
// 	APPEND,
// 	PIPE,
// } e_type ;

// typedef enum {
// 	,
// 	,
// 	,
// 	,
// } e_error ;

// typedef struct s_tree {
//     e_type    type;
//     char    **command;          // La commande et ses arguments (si type = COMMAND)
//     struct  s_node *left;       // Enfant gauche (pour PIPE ou REDIRECT)
//     struct  s_node *right;      // Enfant droit (pour PIPE ou REDIRECT)
//     // struct  s_node *parent;     // Pointeur vers le parent
//     char    *filename;          // Nom du fichier (si type = REDIRECT)
// } t_tree;


// void    check_type_cmd(char **cmd);
// void    execute_builtin(char **cmd);
// void	handle_executable(char **cmd);

// tokenization
char	**split_into_tokens(char *s);
char	*skip_space(char *s);
char	*iterate_word(char *s);
char	*skip_quotes(char *s, char quote);
char	*iterate_inside_quotes(char *s, char quote);
char	*handle_quote(char *s, char quote);
void	handle_arr(char *s, char **arr, int *count, char *start_string);
void	free_arr_tokenization(char **arr);

// tokenization - quote verifications
int		find_last_quote(char *s, char quote);
int		is_space_before_quote(char *s);

#endif