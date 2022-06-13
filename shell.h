#ifndef  SHELL_H
#define SHELL_H
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <dirent.h>


typedef struct s_shell {
	char **tab_save_env;
	char **tab_save_exp;
	char *save_pwd;
	char *save_old_pwd;
	char **save_all_namefiles;
	int	*all_fd;
	int	counter;
}   t_shell;

typedef struct t_list
{
    char            **val;
    int             *v_type;
    struct t_list   *next;
	struct t_list	*prev;
}t_list;

unsigned int status_exec_g;
//utils libft

char	*ft_substr(char *s, unsigned int start, size_t len);
size_t  ft_strlen(char *src);
char	**ft_split(char *s, char l);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int c);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *s,	int fd);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
void	*ft_calloc(size_t n, size_t c);
char	*get_next_line(int fd);
char	*ft_strstr(char *str, char *to_find, int size);
char	*ft_strstr2(char *str, char *to_find, int size);
int	ft_isdigit(int c);
int find(char *str);
int	ft_strcmp(char *s1, char *s2);
int	ft_isdigit(int c);


int check_herd(t_shell *mini, t_list *list);
void    pipes(t_shell *mini, t_list *list);
int     len(char *str);
void    ft_print(t_shell *index, int fd);
void    ft_realloc(t_shell *index, char *str, int save);
int     duplicate_exp(t_shell *index, char *string, char *add_str, int i);
//int		find_space(char *str);
void	ft_print_export(t_shell *index, char **str, int fd);
int     add_str_tab_exp(t_shell *index, char *str);
int     check_duplicate(t_shell *index, char *str);
void	exec_cmd(t_shell *mini, t_list *lst);
void	ft_check_cmd(t_shell *mini, t_list *list);
char	*check_path_if_exi(t_shell *mini);
void    ft_echo(t_shell *mini, char **str, int fd);
void    ft_check_built(t_shell *mini, t_list *lst, int fd);
void    ft_redirection(t_shell *mini, t_list *lst, int a, int tem_fd);
//int     checker(char *str);
int     finder(char *str);
//int     find_pipe(char *str);
int		invalide_identifier(char *str, int fd);
void    heredoc(t_shell *mini, t_list *list, int num, int fd_out);
int     open_all_files(t_list *list, int a);
void	red_in(t_shell *mini, char *str);
int    ft_and_bonus(t_shell *mini, char *str);
//int	    exec_pipe(t_shell *mini, char *tab);
void    ft_or_bonus(t_shell *mini, char *str);
int		search_path_in_env(t_shell *mini, int a);
//char **ft_parse(char *str);
int find_both(char *str);
void    ft_both(t_shell *mini, char *str);
void    ft_wildcars(t_shell *mini, char *str);
void    ft_redin(t_shell *mini, t_list *lst, int te_fd, int num);

// exit

void    ft_exit(char *str, int fd);
void    ft_env(t_shell *index, int fd);
void    ft_unset(t_shell *index, char **str, int fd);
void    ft_cd(char *path, t_shell *mini);
void	ft_pwd(int fd);
int     tablen(char **tab);
int	    ft_pipe(t_shell *mini, char *str);
char 	**save_cmd(t_list *list);

#endif