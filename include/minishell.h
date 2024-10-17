/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/12 20:34:15 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>

// typedef struct s_data
// {
    
// }			t_data;

typedef enum {
    RREDIRECTION,
    LREDIRECTION,
    APPEND,
    PIPE,
} e_type ;

typedef struct s_tree {
    e_type    type;
    char    **command;          // La commande et ses arguments (si type = COMMAND)
    struct  s_node *left;       // Enfant gauche (pour PIPE ou REDIRECT)
    struct  s_node *right;      // Enfant droit (pour PIPE ou REDIRECT)
    // struct  s_node *parent;     // Pointeur vers le parent
    char    *filename;          // Nom du fichier (si type = REDIRECT)
} t_tree;


void    check_type_cmd(char **cmd);
void    execute_builtin(char **cmd);
void	handle_executable(char **cmd);
#endif