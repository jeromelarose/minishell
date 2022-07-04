/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 14:47:32 by jelarose          #+#    #+#             */
/*   Updated: 2020/10/11 19:52:16 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# define SHELL "minishell"

typedef struct		s_stock
{
	int				fd;
	char			*str;
}					t_stock;

typedef struct		s_env
{
	char			**envp;
	char			**expt;
	char			**var;
	char			***list;
	int				*fd;
	int				fd_nb;
	int				fd_size;
	char			**lst_cmd;
	int				stdo;
	int				stdi;
	char			quote;
	int				sl;
	char			*line;
	int				sigc;
	int				**tab_pip;
	int				*tab_fork;
	int				nb_pip;
	int				nb_fork;
}					t_env;

t_env				g_shell;

int					nb_format(int i, int nb, char *line);
int					nb_format2(int *i, int nb, char *line);
int					is_nstr(char *str, char *set, int size);
void				sort_tab_str(char **tab);
int					is_num(char *str);
char				**ft_free_tab(char **tab);
char				**ft_free_tab(char **tab);
void				free_int(int **str);
void				free_str(char **str);
int					open_fd(char *line, int *fd, int i);
char				*ft_strndup(char *src, int nb);
int					gest_equal(char **list);
int					format_slash(void);
int					verif_line(void);
char				*ret_dir(char *cmd);
void				free_all_fork(void);
void				gest_quote(char *line, int i);
int					ft_atoi(char *str);
int					print_error(char **args, char *line, char *msg, int nb);
void				get_exit_code(int status);
int					is_bultin(char **args);
int					is_first_bultin(char **args);
char				*ft_itoa(long long int nb);
int					add_var(char *name, char *valeur);
int					ft_strlen_set(char *str, char set);
char				**ret_lst_cmd();
char				*ret_vars(char *var);
char				*ft_strdup(char *src);
char				*ft_strchr(const char *s, int c);
char				*ft_strcat_mal(char *s1, char *s2, unsigned size);
int					get_next_line(int fd, char **line);
char				**ft_split(char *str, char *charset);
char				**ft_split_save(char *str, char *charset);
char				**ft_split_string(const char *str, char *charset);
void				free_lst_str(char ***lst);
void				free_lst_tabstr(char ****lst);
int					redir(char *line);
void				close_fd(void);
char				***ret_list(char *line);
int					cmd(char ***list, int i, int y);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strlen(char *str);
int					select_bultin(char **args);
int					bultin_env(char **args);
int					bultin_exit(char **args);
int					bultin_unset(char **args);
int					bultin_echo(char **args);
int					bultin_export(char **args, int i);
char				*get_pwd();
int					ft_strncmp(const char *s1, const char *s2, size_t size);
char				*ret_env(char **env, char *path);
int					sup_envp(char ***envp, char *path);
int					copy_envp(char ***envp, char **copy, int size);
int					size_envp(char **env);
int					is_envp(char **envp, char *path, int nb);
int					replace_envp(char **env, char *path, int more);
int					add_envp(char ***env, char *path, int more);
int					creat_env();
int					is_str(char *str, char c);
void				ft_strcat(char *s, char *s2);
int					file_exists(char *ptr_file);
int					switch_quote(char *s, int i, char *c);
char				*ret_var(char *path);
char				*format(char *line, int i, int y);
void				free_cmd(void);
void				init(void);
int					ret_nb_fork(char ***list);
int					ret_id_fd(char ***list, int end);
int					ret_nb_pip(char ***list, int size);
void				free_cmd(void);
void				close_cmd(int **fd);
void				verif_file(int i, int nb);
char				*format_tilde(char *str, char *ret, char *home);
int					nb_tilde(char *str, char *home);
char				*org_line(char *line);
int					bultin_cd(char **args);
int					nb_org(char *line);
int					verif_ambigue(char *line);
int					insert_char(int c, int *sl, char cur, char next);
char				*error_symbole(char c, int i);
char				*ret_pwd_prompt(void);
void				prompt(void);
char				*del_more(char *line, int *more);

#endif
