/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaloiu <dgaloiu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:44:57 by trobert           #+#    #+#             */
/*   Updated: 2022/10/29 16:08:19 by dgaloiu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H 

# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>

# define TOKEN_ERR "syntax error near unexpected token "
# define HDEOF_ERR "warning: here-document delimited by end-of-file\n"
# define DUP2_ERR "dup2 has failed\n"
# define NOT_VALID_ID ": not a valid identifier\n"
# define UNSET_ERR "unset: ' %s ' : not a valid identifier\n"
# define ENV_ERR_1 "env: No such file or directory\n"
# define ENV_ERR_2 "env: Arguments or options not managed\n"
# define EXIT_ERR_1 "exit: too many arguments\n"
# define NUM_ARG_REQ ": numeric argument required\n"
# define CD_ARGS_ERR "cd: too many arguments\n"
# define NOENT ": No such file or directory\n"
# define NOTDIR ": Not a directory\n"
# define PERM_DENIED ": Permission denied\n"
# define OPT_NOT_MANAGED ": Option not managed"
# define CD_ERR_GETCWD "cd: error retrieving current directory: \
getcwd: cannot access parent directories"

//metachar not used = "* [ ] ; || && ( ) # \ ` $()"

# define MISUSE_SHELL 2
# define NOT_EXECUTABLE 126 
# define CMD_NOT_FOUND 127 
# define CTR_C_SIGNAL 130
# define COREDUMP 131

extern int	g_var;

enum e_wordtype
{
	UNDEFINED,
	COMMAND,
	VAR,
	OPTION,
	BUILTIN,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	LIMITER,
	APPEND,
	DIRFILE,
};

enum e_var_type
{
	CHAR,
	STR,
	TAB_STR,
	TAB_INT,
	S_LIST,
	S_LIST_PTR,
	S_BLOCK,
	S_BLOCK_PTR,
	S_ELEM,
	S_ELEM_PTR,
	S_ENV,
	S_PIPEX,
	S_DATA,
	S_ARG_ENV,
	FREE_PTR,
	FREE_ALL,
	RDL,
};

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
	struct s_list	*prev;
	enum e_wordtype	type;
}	t_list;

typedef struct s_free_list
{
	void				*ptr;
	enum e_var_type		type;
	struct s_free_list	*prev;
	struct s_free_list	*next;
}	t_free_list;

typedef struct s_block
{
	t_list			**tokenlst;
	char			**cmd;
	int				id;
	int				fd_in;
	int				fd_out;
	int				fd_hd;
	char			*limiter;
	char			*hd_name;
	struct s_block	*next;
	struct s_block	*prev;
}	t_block;

typedef struct s_elem
{
	int				len;
	char			type;
	int				count;
	int				index_start;
	char			*str;
	char			*arg;
}	t_elem;

typedef struct s_env
{
	char			**envp;
	char			*pwd;
	int				envp_size;
	char			*path_envp;
	char			*home;
	char			**cache;
}	t_env;

typedef struct s_pipex
{
	int				index;
	int				status;
	int				cmd_nbr;
	char			pipe_nbr;
	int				**pipefd;
	int				*pid;
	char			*path_cmd;
	char			**potential_paths;
}	t_pipex;

typedef struct s_data
{
	t_list			**lst;
	t_list			**lst_arg;
	t_env			*env_data;
	t_block			**block;
	t_pipex			*pipex;
	int				last_status;
	int				nbr_block;
	int				nbr_pipe;
	int				is_var;
	int				flag_relou;
	int				saved_stdin;
	int				saved_stdout;
	int				saved_stdin_loop;
	int				hered_err_mode;
	int				hered_err_fd;
}	t_data;

typedef struct s_arg_env
{
	char			*name;
	char			*value;
	int				existing;
}	t_arg_env;

/* ************************************************************************** */
/*                         LAUNCHING AND INIT MINISHELL                       */
/* ************************************************************************** */

void		init_minishell(t_data *data, char *envp[]);
void		init_var(t_data *data, char *envp[]);

/* ************************************************************************** */
/*                               ENVP FUNCTIONS                               */
/* ************************************************************************** */

char		*find_var_envp(t_data *data, char *var_to_find);

/* ************************************************************************** */
/*                         PARSING (not so)FUNsCTIONS                         */
/* ************************************************************************** */

int			get_in_lst(t_data *data, char *str, t_list **lst);
void		addtolist(t_list **lst, char *cpy, enum e_wordtype type);
void		ft_parse(t_data *data, t_list **lst_arg, char *old_arg);
int			begins_by_dollar(t_data *data, t_elem *e, int i, int j);
void		ft_quotes(t_data *data, t_elem *e, int i);
char		*lstjoin_arg(t_list **lst_arg);
void		parse_in_block(t_data *data, t_list **lst);
void		ft_littlelst(t_list **new, t_list *start, t_list *end);
void		init_tokens_list(t_list **tokenlst);
void		set_tokens_block(t_block **block);
void		split_export_arg(t_data *data, char *str);
void		split_export_arg2(t_data *data, char *tmp_str, t_list **lst);
t_block		*ft_blocklast(t_block *block);
char		**ft_split_quote(char *str, char *charset);
int			is_same_char(char c, char *charset);

/* ************************************************************************** */
/*                               CHECK SYNTAX                                 */
/* ************************************************************************** */

void		check_first_token_dir(t_block **block);
int			check_bonus_error(t_list **list);
int			check_sep_error(char *str);
int			check_syntax(t_data *data, t_list **lst);
int			is_redir(t_list *lst);
int			is_pipe(t_list *lst);
int			msg_syntax_redir(t_list *tmp);
int			check_last_pipe(t_list **lst_arg);
int			check_first_pipe(t_list *lst);

/* ************************************************************************** */
/*                         GET CMDS AND PATH FUNCTIONS                        */
/* ************************************************************************** */

char		**get_envp(t_data *data, char *envp[]);
char		*get_path_envp(t_data *data, char **envp);
char		*get_home_var(t_data *data, char *envp[]);

/* ************************************************************************** */
/*                               	I/O REDIR                                 */
/* ************************************************************************** */

int			open_all_files(t_data *data, t_block **block);
int			openfile_redir_in(t_list *lst, t_block *block);
int			openfile_heredoc(t_data *data, t_list *lst, t_block *block);
int			openfile_heredoc2(t_list *lst, t_block *block);
int			openfile_redir_out(t_list *lst, t_block *block);
int			openfile_append(t_list *lst, t_block *block);
int			open_heredoc_block(t_data *data, t_block *block, t_list **tokenlst);
int			is_file(char *pathname, char *cmd);
void		close_all_files(t_block **block);
void		close_saved_dup(t_data *data);
int			check_redir_heredoc(t_list **lst);
int			hered_mode(t_data *data, t_block *b);
void		get_limiter_str(t_block *b, t_list *lst);
void		hered_error(t_data *data, t_block **block);
void		hered_mode_gnl(t_data *data, int fd, char *limiter);

/* ************************************************************************** */
/*                               EXEC AND PIPE                                */
/* ************************************************************************** */

char		*ft_cmdjoin(char *s1, char *s2);
char		**set_cmd_execve(t_list **tokenlst);
void		init_var_pipex(t_data *data);
int			ft_pipex(t_data *data);
void		exec_cmd(t_data *data, t_pipex *p, t_block *b, char **envp);
int			exec_one_builtin(t_data *data, t_block *b, char **cmd);
int			check_file(char *pathname);
int			check_start_pipex(t_data *data);
void		close_pipes(t_pipex *p, int i);
void		close_all_pipes(t_pipex *p);
void		get_status_wait(int status);
void		free_all_pipex(t_data *data, t_pipex *p);
void		error_exit(char *err, char *strerr);

/* ************************************************************************** */
/*                                 BUILTINS                                   */
/* ************************************************************************** */

int			is_builtin(char *str);
int			is_same(char *str1, char *str2);
void		ft_export(t_env **data, char **args);
int			manage_arg_export(t_env **data, t_arg_env arg);
void		add_var_to_env(t_env **env_data, t_arg_env arg);
void		print_env_ascii(t_env **data);
int			uncorrect_var_name_export(char *str);
void		clean_plus(t_arg_env *arg);
t_arg_env	*get_export_vars(char **tab, int nb);
int			printing_tab_sorted_util(void);
void		update_var_to_env_append(t_env **env_data, int line, t_arg_env arg);
int			manage_arg_export_append(t_env **data, t_arg_env *arg);
void		update_var_to_env(t_env **env_data, int line, t_arg_env arg);
void		free_arg_struct(t_arg_env *arg, int nb);
int			get_nb_args_export(char **tab);
char		*get_value_of(t_env **data, char *name);
char		**envpdup_and_add_var(t_env **data, t_arg_env arg);
int			new_value(t_env **data, int line, char *old_value);
int			varline(t_env **data, char *name);
int			valid_str_env(char *str);
void		update_env_pwd(t_env **data, char **args);
void		double_slash_pwd(t_env **data, char *tmp);
void		ft_echo(char **arg);
void		ft_unset(t_env **data, char **args);
void		ft_env(t_env **data, char **args);
void		ft_exit(t_data *data, char **args);
void		too_much_args_exit(t_data *data);
int			get_modulo_256_of(unsigned long long int nb, int flag);
void		numeric_arg_req_exit(t_data *data, char **args);
void		getcwd_error(void);
void		ft_cd(t_env **data, char **args);
void		ft_pwd(t_env **data);
void		maj_shlvl(t_env **data);
int			get_size_of_tab(char **tab);
char		**add_export_tab(t_env **data, t_arg_env arg);
char		*clean_arg_value(char *value);
char		**remove_from_cache(t_env **data, char *str);

/* ************************************************************************** */
/*                                LIBFT UTILS                                 */
/* ************************************************************************** */

int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isascii_ext(int c);
void		ft_bzero(void *s, int n);
int			ft_strlen(char *str);
char		*ft_strdup(char *src);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_chardup(char c);
char		*ft_strnstr(char *str, char *to_find, int n);
char		*ft_strdup_index(const char *src, int start, int end);
char		**ft_split(char *str, char c);
int			ft_strcmp(char *s1, char *s2);
int			is_same_str(char *s1, char *s2);
char		*ft_itoa(int n);
int			ft_atoi(char *nptr);
char		**ft_tabjoin(char **tab1, char **tab2);

/* ************************************************************************** */
/*                               PRINTING UTILS                               */
/* ************************************************************************** */

int			ft_putchar_fd(int fd, int c);
void		print_no_file_cd(char *str);
void		print_not_dir_cd(char *str);
void		print_not_acces_cd(char *str);
void		print_opt_not_managed_echo(char *str);
int			print_export_1(char *value);
int			print_export_2(char *name);
int			print_export_3(t_arg_env arg);
int			print_export_4(char *value);
int			print_export_5(char *name);
int			print_export_6(t_arg_env arg);
void		print_error_path(char *path, char *error);
void		print_sep_error_double(char c);
void		print_sep_error_simple(char c);
void		print_hered_fail(char *error);
void		print_hered_dup_fail(char *error);
void		print_hered_dup_fail2(char *error);
void		print_redir_error(void);
void		print_single_pipe_error(void);
void		print_newline_error(void);

/* ************************************************************************** */
/*                               LIST FUNCTIONS                               */
/* ************************************************************************** */

t_list		*ft_lstnew(char *content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		set_prev_lst(t_list **lst);

/* ************************************************************************** */
/*                               FREE FUNCTIONS                               */
/* ************************************************************************** */

char		**free_all_split(char **tab, int k);
int			free_int_split(int **tab, int i);
int			free_split(char **tab);
void		free_lst(t_list *lst);
void		free_lst2(t_list **lst);
void		free_block(t_block **block);
void		free_data(t_data *data);
void		error_free_quit(t_data *data, char *str);

/* ************************************************************************** */
/*                                  SIGNALS                                   */
/* ************************************************************************** */

void		signal_handler(int sig);
void		signal_quit(int sig);

/* ************************************************************************** */
/*                                   godmalloc                                */
/* ************************************************************************** */

void		*godmalloc(void *ptr, int size, enum e_var_type type);
void		*case_char(void);
void		*case_str(int size);
void		*case_tab_str(int size);
void		*case_tab_int(int size);
void		*case_s_list(void);
void		*case_s_list_ptr(void);
void		*case_s_block(void);
void		*case_s_block_ptr(void);
void		*case_s_elem(void);
void		*case_s_elem_ptr(void);
void		*case_s_env(void);
void		*case_s_pipex(void);
void		*case_s_data(void);
void		*case_s_arg_env(int size);
int			free_malloc(t_free_list **lst,
				void *to_add, enum e_var_type flag);
void		pl_in_middle(t_free_list **lst);
t_free_list	*pl_in_beggin(t_free_list **lst);
void		put_list_back(t_free_list **lst, t_free_list *tmp);
void		*godmalloc_readline(t_free_list **lst, void *ptr,
				enum e_var_type type);
void		end_all_malloc_failed(t_free_list **lst);

#endif
