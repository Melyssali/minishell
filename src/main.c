/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/31 10:48:29 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// les redirections :
//  < 	(commande < fichier.txt) doit rediriger l’entrée. Si le fichier existe, il est simplement utilisé comme source d'entrée. Pas de troncature ni d'ajout, juste une lecture du fichier.
//  > 	(echo "Nouveau contenu" > fichier.txt) doit rediriger la sortie. Si le fichier existe, son contenu est truncaté (écrasé) et remplacé par la nouvelle sortie de la commande.
//  << 	(commande << DELIMITEUR) doit recevoir un délimiteur et lire l’input donné jusqu’à rencontrer une ligne
// 		contenant le délimiteur. Cependant, l’historique n’a pas à être mis à jour !
//	>> 	(echo "Ajouté à la fin" >> fichier.txt) doit rediriger la sortie en mode append (ajout à la fin du fichier).
//  | 	doit rediriger la sortie de la commande à gauche du pipe vers l’entrée de la commande à droite du pipe.

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell % ");
		if (input == NULL)
			break ;
		// add_history(input);
		split_into_tokens(input);
		// check_type_cmd(cmd);
		// if (ft_strcmp(cmd[0], "exit") == 0)
		// 	break ;
	}
	return (0);
}
