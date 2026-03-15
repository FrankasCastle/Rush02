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

int	get_file_size(char *filename)
{
	int		dict_cont;
	int		bytes;
	int		total;
	char	tmp[1000];

	total = 0;
	dict_cont = open(filename, O_RDONLY);
	if (dict_cont < 0)
		return (-1);
	bytes = read(dict_cont, tmp, 1000);
	while (bytes > 0)
	{
		total = total + bytes;
		bytes = read(dict_cont, tmp, 1000);
	}
	close(dict_cont);
	if (bytes < 0)
		return (-1);
	return (total);
}

int	read_file_content(char *filename, char *buffer, int size)
{
	int	dict_cont;
	int	bytes;
	int	total_read;

	dict_cont = open(filename, O_RDONLY);
	if (dict_cont < 0)
		return (-1);
	total_read = 0;
	bytes = read(dict_cont, buffer + total_read, size - total_read);
	while (bytes > 0)
	{
		total_read = total_read + bytes;
		bytes = read(dict_cont, buffer + total_read, size - total_read);
	}
	close(dict_cont);
	if (bytes < 0)
		return (-1);
	buffer[total_read] = '\0';
	return (total_read);
}

char	*dict_reader(char *filename)
{
	int		size;
	char	*buffer;

	size = get_file_size(filename);
	if (size < 0)
		return (NULL);
	buffer = (char *)malloc(size + 1);
	if (buffer == NULL)
		return (NULL);
	if (read_file_content(filename, buffer, size) < 0)
		return (free(buffer), NULL);
	return (buffer);
}