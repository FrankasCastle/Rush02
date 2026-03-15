#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_dict
{
	char	*key;
	char	*value;
}	t_dict;

int	print_error(char *message);
int		ft_strlen(char *str);
void	ft_putstr(char *str);
int		ft_strcmp(char *s1, char *s2);
int		get_file_size(char *filename);
int		read_file_content(char *filename, char *buffer, int size);
char	*dict_reader(char *filename);
int		ft_is_space(char c);
char	*ft_strdup_range(char *src, int start, int end);
void	skip_line_breaks(char *buffer, int *index_dict);
void	skip_inline_spaces(char *buffer, int *index_dict);
int		count_dict_entries(char *buffer);
int		get_key(char *buffer, int *index_dict, t_dict *dict, int count);
int		get_value(char *buffer, int *index_dict, t_dict *dict, int count);
int		parse_dict(char *buffer, t_dict *dict, int max_dict);
int		str_conv(char *str);
char	*ft_dict_get(int key, t_dict *dict, int size);
void	print_dict_value(int key, t_dict *dict, int size);
void	free_dict(t_dict *dict, int size);
void	print_two_digits(int du, t_dict *dict, int size);
void	print_hundred_part(int c, int du, t_dict *dict, int size);
void	number_translator(char *str, t_dict *dict, int size);
void	init_groups(char groups[11][4]);
void	fill_groups(char *str, char groups[11][4]);
int		is_zero_group(char group[4]);
void	print_scale_by_position(int pos, t_dict *dict, int size);
void	translate_full_number(char *str, t_dict *dict, int size);

void	print_two_digits(int du, t_dict *dict, int size)
{
	int	d;
	int	u;

	d = du / 10;
	u = du % 10;
	if (du == 0)
		return ;
	if (du < 10 || (du >= 10 && du < 20))
	{
		print_dict_value(du, dict, size);
		return ;
	}
	print_dict_value(d * 10, dict, size);
	if (u != 0)
	{
		write(1, " ", 1);
		print_dict_value(u, dict, size);
	}
}

void	print_hundred_part(int c, int du, t_dict *dict, int size)
{
	if (c == 0)
		return ;
	print_dict_value(c, dict, size);
	write(1, " ", 1);
	print_dict_value(100, dict, size);
	if (du != 0)
		write(1, " ", 1);
}

void	number_translator(char *str, t_dict *dict, int size)
{
	int	c;
	int	d;
	int	u;
	int	du;

	c = str[0] - '0';
	d = str[1] - '0';
	u = str[2] - '0';
	du = (d * 10) + u;
	print_hundred_part(c, du, dict, size);
	print_two_digits(du, dict, size);
}