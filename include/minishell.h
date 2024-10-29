/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/29 13:36:14 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR -1

// # define PIPE "|"
// # define REDIR_INPUT "<"
// # define REDIR_OUTPUT ">"
// # define HEREDOC "<<"
// # define APPEND_OUTPUT ">>"

# define SQUOTE '\''
# define DQUOTE '\"'
# define SPACE ' '
# define TAB '\t'
# define NEWLINE '\n'

# define TABLE_BUILTINS_SIZE 11
# define TABLE_OPERATORS_SIZE 7

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum
{
	REDIR_OUTPUT,
	APPEND_OUTPUT,
	REDIR_INPUT,
	HEREDOC,
	PIPE
}							e_operators;
// hash table for builtins
typedef struct s_hash_builtin
{
	char					*key;
	struct s_hash_builtin	*next;
}							t_hash_builtins;
// hash table for operators
typedef struct s_hash_operators
{
	char					*key;
	int						type;
	struct s_hash_operators	*next;
}							t_hash_operators;

typedef struct s_command_line
{
	char					**command;
	int						is_builtin;
	char					*input_file;
	char					*output_file;
	int						append_output;
	char					*heredoc_delimiter;
	struct s_command_line	*next;
}							t_command_line;

// tokenization
char						**split_into_tokens(char *s);
char						*skip_space(char *s);
char						*iterate_word(char *s);
char						*skip_quotes(char *s, char quote);
char						*iterate_inside_quotes(char *s, char quote);
char						*handle_quote(char *s, char quote);
void						handle_arr(char *s, char **arr, int *count,
								char *start_string);
void						free_arr_tokenization(char **arr);

// Parsing
t_command_line				*parsing(char *tokens[]);
t_command_line				*create_node(t_hash_operators *table_operators[],
								char *tokens[], int *index,
								t_hash_builtins *table_builtins[]);
int							calculate_width(t_hash_operators *table_operators[],
								char *tokens[], int *index);
int							is_builtin_command(char *cmd,
								t_hash_builtins *table_builtins[]);

// tokenization - quote verifications
int							find_last_quote(char *s, char quote);
int							is_space_before_quote(char *s);

// hash table builtins
void						initialize_builtins(t_hash_builtins *table_builtins[]);
int							search(t_hash_builtins *table[], char *key);

// hash table operators
void						initialize_operators(t_hash_operators *table_operators[]);
int							get_operator_type(t_hash_operators *table_operators[],
								char *str);

#endif