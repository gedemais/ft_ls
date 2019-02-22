/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:52 by gedemais          #+#    #+#             */
/*   Updated: 2019/02/22 07:06:49 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define TF ((t_file*)add[i])
# define TFVAR ((t_file*)add[vars[4]])
# define TF0 ((t_file*)add[0])
# define TF1 ((t_file*)add[1])
# define TFN1 ((t_file*)n1)
# define TFN2 ((t_file*)n2)
# define TFAS ((t_file*)add[start])
# define TFAE ((t_file*)add[end - 1])
# define TFAJ ((t_file*)add[j])
# define TFAP ((t_file*)add[pivot])

# define WBUFF_SIZE 8192

# define DEBUG 0
# define DEBUGPARAMS 1
# define PUT ft_putstr("There\n");
# define PUT1 ft_putstr("There1\n");
# define PUT2 ft_putstr("There2\n");
# define PUT3 ft_putstr("There3\n");
# define PUT4 ft_putstr("There4\n");
# define PUT5 ft_putstr("There5\n");
# define PUT6 ft_putstr("There6\n");
# define PUT7 ft_putstr("There7\n");
# define PUT8 ft_putstr("There8\n");
# define PUT9 ft_putstr("There9\n");

# define O_L 1
# define O_RMAJ 2
# define O_A 4
# define O_R 8
# define O_T 16
# define O_F 32
# define O_SMAJ 64

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

typedef struct	s_file t_file;

struct		s_file
{
	char	*name;
	int		name_len;
	char	*perms;
	char	*uid;
	int		uid_len;
	char	*gid;
	int		gid_len;
	int		dir;
	int		nlinks;
	int		size;
	int		blocksize;
	char	*secstime;
	char	*date;
	int		day;
	int		year;
	char	*file_path;
	int		nope;
	t_file	*next;
};

typedef struct	s_date
{
	int		year;
	int		month;
	int		day;
	int		hour;
	int		mins;
	int		secs;
}				t_date; 

// main.c
void		ft_write_buff(char *str, char c, int cat, int flush);
int			ft_ls(char **params, int mask, char *path);
int			ft_relaunch_check(t_file *file, int mask);

// display_fts.c
int			ft_nohiddens(int nbf, void **add);
int			ft_flags(t_file *node, int mask);
void		ft_add_links(int nb, int max);
void		ft_add_date(char *date);
void		ft_get_lines_data(void **add, int *max, int nbf);

// ft_address.c
void		**ft_addresses(t_file *lst, int len);
void		**ft_addrev(void **add, int mask);

// ft_datecmp.c
int			ft_datecmp(char *d1, char *d2, char *n1, char *n2);

// ft_run.c
void		ft_run(int mask, int nbf, void **add);

// ft_list.c
int			ft_lstlen(t_file *lst);
void		ft_display_ls_lst(t_file *top);
t_file		*ft_ls_lstnew(char *path, char *name, int mask);
int			ft_ls_pushfront(t_file **file, t_file *new);
t_file		*ft_make_list(char *path, int mask);

// ft_params.c
void		ft_params(char **params, int mask, char *path);
char		*ft_new_path(char *path, char *param);

int			ft_display_lines(void **add, int nbf, int mask);
// ft_parsing.c
int			ft_is_flag(char c);
int			ft_count(int argc, char **argv);
int			ft_get_options(int ac, char **av, int *i, int mask);
char		**ft_get_params(int ac, char **av, char **data, int i);
char		**ft_parse_input(int ac, char **av, int *mask);

// ft_quicksort.c
void		ft_swap_nodes(t_file *n1, t_file *n2, int mask);
void		**ft_addresses (t_file *lst, int len);
int			ft_sort_params(char **tab, int start, int end);
int			ft_ls_quicksort(void **add, int start, int end, int mask);

// ft_display_lines.c
void		ft_add_total(int total);
int			ft_display_lines(void **add, int nbf, int mask);
void		ft_add_uid(char *uid, int uid_len, int len);

// ft_display_cols.c
int			ft_getless(void **add, int nbf, int npl, int minw);
int			ft_display_cols(int mask, void **add, int nbf, int minw);

// ft_display_line.c
void		ft_cpy_string(char *str);
void		ft_pad_string(int minw, int name_len);
int			ft_display_line(int mask, void **add, int nbf, int minw);

// ft_usage.c
void		ft_usage(int type, char wrong, char *wrong_name, int usage);

// fts.c
int			ft_tablen(char **tab);
char		**ft_tabdel(char **tab);
int			ft_add_mask(int mask, char c);
int			ft_get_screen_length(void);
int			ft_find_biggest(void **add, int nbf);
int			ft_find_longest(void **add);
int			ft_find_fattest(void **add);

// ft_singletons.c
int			*ft_last_endl(void);

#endif
