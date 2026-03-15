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

int	get_key(char *buffer, int *index_dict, t_dict *dict, int count)
{
	int	start;

	start = *index_dict;
	while (buffer[*index_dict] >= '0' && buffer[*index_dict] <= '9')
		(*index_dict)++;
	if (*index_dict == start)
		return (0);
	dict[count].key = ft_strdup_range(buffer, start, *index_dict);
	if (dict[count].key == NULL)
		return (0);
	return (1);
}

int	get_value(char *buffer, int *index_dict, t_dict *dict, int count)
{
	int	start;
	int	end;

	while (buffer[*index_dict] && buffer[*index_dict] != ':'
		&& buffer[*index_dict] != '\n')
		(*index_dict)++;
	if (buffer[*index_dict] != ':')
		return (0);
	(*index_dict)++;
	skip_inline_spaces(buffer, index_dict);
	start = *index_dict;
	while (buffer[*index_dict] && buffer[*index_dict] != '\n')
		(*index_dict)++;
	end = *index_dict;
	while (end > start && ft_is_space(buffer[end - 1]))
		end--;
	dict[count].value = ft_strdup_range(buffer, start, end);
	if (dict[count].value == NULL)
		return (0);
	return (1);
}

int	parse_dict(char *buffer, t_dict *dict, int max_dict)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (buffer[i] && count < max_dict)
	{
		skip_line_breaks(buffer, &i);
		skip_inline_spaces(buffer, &i);
		if (buffer[i] == '\0')
			break ;
		if (get_key(buffer, &i, dict, count) == 0)
			break ;
		skip_inline_spaces(buffer, &i);
		if (get_value(buffer, &i, dict, count) == 0)
			break ;
		if (buffer[i] == '\n')
			i++;
		count++;
	}
	return (count);
}