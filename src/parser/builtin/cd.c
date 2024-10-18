/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/17 14:15:54 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../../include/minishell.h"

// int ft_cd(char **cmd)
// {
//     if (ft_strcmp(cmd[0], "cd") == 0)
//     {
//         if (cmd[1] == NULL)
//         {
//             printf("minishell: cd: argument manquant\n");
//             return(1);
//         }
//         else
//         {
//             if (chdir(cmd[1]) == 0)
//             {
//                 if (getcwd(cwd, sizeof(cwd)) != NULL)
//                 {
//                     printf("Répertoire changé avec succès : %s\n", cwd);
//                     return(0);   
//                 }
                    
//             }
//             else
//             {
//                 perror("chdir() erreur");
//                 return(1);
//             }
//         }
//     }
// }