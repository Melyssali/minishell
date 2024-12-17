/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/17 12:51:02 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# define ERROR -1
# define SQUOTE '\''
# define DQUOTE '"'
# define DOLLAR '$'
# define SPACE ' '
# define TAB '\t'
# define NEWLINE '\n'
# define FAIL 1
# define SUCCESS 0
# define TRUE 1
# define FALSE 0
# define SAVE 0
# define RESTORE 1
#define INITIAL_SIZE 10

# define TABLE_BUILTINS_SIZE 11
# define TABLE_OP_SIZE 11

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h> // for perror
#include <sys/wait.h> //for waitpid
#include "../libs/libft/libft.h"
#include <limits.h>

typedef enum
{
	REDIR_OUTPUT,
	APPEND_OUTPUT,
	REDIR_INPUT,
	HEREDOC,
	PIPE
}		
					e_operators;
typedef enum
{
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET
}					e_builtins;

typedef enum
{
	COMMAND = 1,
    OPERATOR,
    OPERATOR_PIPE,
    ARGUMENT,
    ARGUMENT_FILE,
    REDIRECTION
}							e_token_type;

typedef struct s_env_var
{
	char *key;
    char *value;
    struct s_env_var *next;
} t_env_var;


// hash table for builtins
typedef struct s_hash_builtin
{
	char					*key;
	int						type;
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
	char					*cmd_path;
	int						is_builtin;
	int						builtin_type;
	char					*input_file;
	char					*output_file;
	int						append_output;
	char					*heredoc_delimiter;
	char 					*heredoc_file;
	struct s_command_line	*next;
}							t_command_line;

typedef struct s_data
{
	t_hash_builtins			*table_builtins[TABLE_BUILTINS_SIZE];
	t_hash_operators		*table_op[TABLE_OP_SIZE];
	char					**tokens;
	char					*variable_value;
	int						*token_types;
	int						pipe_count;
	int						previous_state;
	int						previous_op_state;
	int						operator_type; 
	int						return_value;
	int						save_stdin;
	int						save_stdout;
	int						is_double_quotes;
}							t_data;

typedef struct s_minishell {
	char			**envp;
	t_env_var		*env;
	t_command_line	*command_line;
	t_data			*data;
}	t_minishell;

// tokenization
char						**split_into_tokens(char *s, t_data *data);
char						*skip_space(char *s);
char						*iterate_word(char *s);
char						*skip_quotes(char *s, char quote);
char						*iterate_inside_quotes(char *s, char quote);
char						*handle_quote(char *s, char quote);
void						handle_arr(char *s, char **arr, int *count,
								char *start_string);
void						free_arr_tokenization(char **arr);
int 						is_operator(char c);

// -- BUILTINS -- 
int 	mini_cd(t_minishell *minishell);
int 	mini_echo(t_minishell *minishell);
int		mini_env(t_minishell *minishell);
int		mini_exit(t_minishell *minishell);
int		mini_export(t_minishell *minishell);
int		mini_pwd(void);
int		mini_unset(t_minishell *minishell);

// -- BUILTINS UTILS -- 
int 	ft_count_args(char **cmd);
char 	*ft_getenv(char *key, t_minishell *minishell);
int 	update_env_value(char *key, char *value, t_minishell *minishell);
void 	copy_env(t_minishell *minishell);
void	declare(t_minishell *minishell);
int 	add_node(char *str, t_minishell *minishell);
int		change_value(t_minishell *minishell, char *equal_sign, int key_len);
// -- EXECUTION -- 
int		execution(t_minishell *minishell);
int		execute_builtin(t_minishell *minishell);
void	parent_process(t_minishell *minishell, int *pipe);
void	child_process(t_minishell *minishell, int *pipe);
int		build_cmd(t_minishell *minishell);
int		exec_cmd(t_minishell *minishell, int *pipe);
int 	exec_loop(t_minishell *minishell);
int 	len_list(t_env_var *list);
char 	**lst_to_arr(t_env_var *env);

// -- FILE_UTILS -- 
int		setup_redirections(t_command_line *command_line, int *pipe);
int		handle_infile(t_command_line *command_line);
int 	handle_outfile(t_command_line *command_line);

// -- EXECUTION UTILS --
int		execute_builtin(t_minishell *minishell);
void    clean_up_node(t_command_line *command_line);
void	skip_and_free(t_minishell *minishell);
int		redirect_input(t_command_line *command_line);
int		redirect_output(t_command_line *command_line);
void	free_table(char **table);
void	init_struct(t_minishell *minishell, char **envp);
void	save_or_restore_fds(t_minishell *minishell, int order);
int		print_error(char *str);

// -- PARSING -- 
t_command_line				*parsing(t_data *data);
void		handle_pipe(t_command_line **new_node, t_command_line **current, t_data *data, int *i);
void	handle_redirections(t_command_line **new_node, t_data *data, int *i);
t_command_line				*create_node(t_hash_operators *table_op[],
								char *tokens[], int *index,
								t_hash_builtins *table_builtins[]);
int							calculate_width(t_hash_operators *table_op[],
								char *tokens[], int *index);
int							is_builtin_command(char *cmd,
								t_hash_builtins *table_builtins[]);

// -- INTERPRETING --

char	**handle_interpreting(t_data *data, t_minishell *minishell);
int		count_variable(char *s);
char	*copy_variable(char *s, int size);
char 	*copy_value(char *token, char *start, char *value, int size);

// -- TOKENISATION - quote verifications --
int							find_last_quote(char *s, char quote);
int							is_space_before_quote(char *s);

// -- hash table builtins --
void						initialize_builtins(t_hash_builtins *table_builtins[]);
int							search(t_hash_builtins *table[], char *key);

// -- hash table operators --
void						initialize_table(t_hash_operators *table[], t_hash_builtins *table_builtins[]);
void						initialize_operators(t_hash_operators *table_op[]);
int							get_operator_type(t_hash_operators *table_op[],
								char *str);

// -- ERROR -- 
int							calculate_array_length(char *tokens[]);
int							handle_operators_error(char *s);
int							handle_error(int *token_types);
int							classify_tokens(t_data *data);

// -- HERE DOC -- 
void						handle_heredoc(char *delimiter, t_command_line *node);
void						fill_lines(char *input, t_command_line *node, int index);

// FREE
void						free_nodes_parsing(t_command_line *head);
void						free_builtins_table(t_hash_builtins *table_builtins[]);
void						free_operators_table(t_hash_operators *table_op[]);
void						free_arr_tokenization(char **arr);
void						free_all(t_command_line *head,
								t_hash_operators *table_op[],
								t_hash_builtins *table_builtins[]);
#endif