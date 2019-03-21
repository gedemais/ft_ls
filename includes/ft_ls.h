/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:52 by gedemais          #+#    #+#             */
/*   Updated: 2019/03/21 16:27:42 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define TF ((t_file*)add[i])
# define TFJ ((t_file*)add[j])
# define TFVAR ((t_file*)add[vars[4]])
# define TF0 ((t_file*)add[0])
# define TF1 ((t_file*)add[1])
# define TFN1 ((t_file*)n1)
# define TFN2 ((t_file*)n2)
# define TFAS ((t_file*)add[start])
# define TFAE ((t_file*)add[end - 1])
# define TFAJ ((t_file*)add[j])
# define TFAP ((t_file*)add[pivot])

# define WBUFF_SIZE 16384

# define SINY 31536000
# define SIND 86400
# define SINH 3600
# define SINM 60

# define O_L 1
# define O_RMAJ 2
# define O_A 4
# define O_R 8
# define O_T 16
# define O_F 32
# define O_SMAJ 64
# define O_AMAJ 128
# define O_M 256
# define O_1 512

# include "../libft/libft.h"
# include <stdbool.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <time.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>

typedef struct s_file	t_file;

struct			s_file
{
	char		*name;
	int			name_len;
	char		*file_path;
	char		*uid;
	int			uid_len;
	char		*gid;
	int			gid_len;
	char		*link;
	int			nlinks;
	int			secstime;
	char		*date;
	int			dir;
	int			size;
	int			blocksize;
	int			nope;
	int			nsfd;
	char		*perms;
	int			minor;
	int			major;
	t_file		*next;
};

typedef struct	s_date
{
	int			year;
	int			month;
	int			day;
	int			hour;
	int			mins;
	int			secs;
}				t_date;

void			ft_write_buff(char *str, char c, int cat, int flush);
int				ft_ls(char **params, int mask, char *path);
void			**ft_addrev(void **add, int mask);
void			**ft_addresses(t_file *lst, int len);
void			**ft_make_add(t_file *lst, int len, int mask);
int				ft_find_param(t_file *lst, char *name);
int				ft_nsfd(t_file *lst, char **params);
int				ft_set_add(void **add, char **params);
int				ft_display_dir(char *new_path);
void			ft_putnbr_buff(int n);
int				ft_display_stream(void **add, int nbf, int mask, int t_len);
char			**ft_tabdel(char **tab);
int				ft_free_add(void **add, int nbf);
int				ft_ls_lstdel(t_file *lst, int mask);
int				ft_lstlen(t_file *lst);
char			*ft_make_perms(struct stat *file);
char			*ft_getlink(t_file *file);
t_file			*ft_ls_lstnew(char *path, char *name, int params);
int				ft_ls_pushfront(t_file **file, t_file *new);
t_file			*ft_make_list(char *path, int mask, int i);
int				ft_count_files(char *path);
char			**ft_get_files(char *path);
void			**ft_make_add(t_file *lst, int len, int mask);
int				ft_find_param(t_file *lst, char *name);
int				ft_nsfd(t_file *lst, char **params);
int				ft_is_flag(char c);
int				ft_set_add(void **add, char **params);
int				ft_display_dir(char *new_path);
int				ft_add_mask(int *mask, char c);
char			*ft_relaunch_condition(t_file *lst, char *param, char *name);
int				ft_make_mask(char *flags);
int				ft_params_relaunch(t_file *lst, char **p, char *path, int m);
int				ft_params(char **params, int mask, char *path);
int				ft_is_flag(char c);
int				ft_add_mask(int *mask, char c);
int				ft_check_doubles(char *flags, char c);
int				ft_count(int ac, char **av);
int				ft_make_mask(char *flags);
int				ft_get_options(int ac, char **av);
char			**ft_make_params(int ac, char **av, int size);
int				ft_check_brackets(int ac, char **av);
char			**ft_parse_input(int ac, char **av, int *mask);
char			*ft_new_path(char *path, char *param);
int				ft_cmp(int mask, t_file *n1, t_file *n2);
void			ft_swap_strs(char *s1, char *s2);
void			ft_swap_str(char **s1, char **s2);
void			ft_swap_nodes(t_file *n1, t_file *n2, int mask);
int				ft_ls_partition(void **add, int start, int end, int mask);
int				ft_sort_params(char **argv, int argc);
int				ft_ls_quicksort(void **add, int start, int end, int mask);
t_file			*ft_loadstrings(char *path, char *name, int mask, t_file *new);
char			ft_makefperms(struct stat *file);
char			*ft_make_perms(struct stat *file);
char			*ft_getlink(t_file *file);
int				ft_check_file(char *name, int mask);
int				ft_display_one(void **add, int nbf, int mask);
int				ft_nonope(int nbf, void **add);
int				ft_display_cols(int mask, void **add, int nbf, int minw);
void			ft_display_lines(void **add, int nbf, int mask);
int				ft_display_line(int mask, void **add, int nbf, int minw);
void			ft_relaunch(void **add, int nbf, int mask);
void			ft_run(int mask, int nbf, void **add);
char			*ft_delspath(char *path);
int				*ft_last_endl(void);
int				ft_usage(int type, char wrong, char *wrong_name, int usage);
int				ft_tablen(char **tab);
int				ft_get_screen_length(void);
void			ft_print_flags(int mask);
void			ft_add_total(int total);
void			ft_add_uid(char *uid, int uid_len, int len);
int				ft_add_links(int nb, int max);
void			ft_add_date(char *date);
void			ft_get_lines_data(void **add, int *max, int nbf);
int				ft_add_linkings(t_file *file);
void			ft_minor_major(int minor, int major, int max);
void			ft_cpy_string(char *str);
void			ft_pad_string(int minw, int name_len);
int				ft_nohiddens(int nbf, void **add);
int				ft_flags(t_file *node, int mask);
int				ft_find_biggest(void **add, int nbf);
int				ft_relaunch_check(t_file *file, int mask);

#endif
