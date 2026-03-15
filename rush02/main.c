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

void	free_dict(t_dict *dict, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(dict[i].key);
		free(dict[i].value);
		i++;
	}
	free(dict);
}

int	is_valid_number(char *str)
{
	int	i;

	if (str[0] == '\0')
		return (0);
	if (str[0] == '0' && str[1] == '\0')
		return (1);
	if (str[0] == '0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

t_dict	*load_dict(char *dict_name, int *size)
{
	char	*buffer;
	t_dict	*dict;
	int		capacity;

	buffer = dict_reader(dict_name);
	if (buffer == NULL)
		return (0);
	capacity = count_dict_entries(buffer);
	dict = (t_dict *)malloc(sizeof(tdict) * capacity);
	if (dict == NULL)
	{
		free (buffer);
		return (0);
	}
	*size = parse_dict(buffer, dict, capacity);
	free(buffer);
	if (*size <= 0)
	{
		free (dict);
		return (0);
	}
	return (dict);
}

void	define_args(int argc, char **argv, char **dict_name, char **number)
{
	if (argc == 2)
	{
		*dict_name = "numbers.dict";
		*number = argv[1];
	}
	else
	{
		*dict_name = argv[1];
		*number = argv[2];
	}
}

int	main(int argc, char **argv)
{
	char	*dict_name;
	char	*number;
	t_dict	*dict;
	int		size;

	if (argc != 2 && argc != 3)
		return (print_error("Error\n"));
	define_args(argc, argv, &dict_name, &number);
	if (is_valid_number(number) == 0)
		return (print_error("Error\n"));
	dict = load_dict(dict_name, &size);
	if (dict == NULL)
		return (print_error("Dict Error\n"));
	translate_full_number(number, dict, size);
	write(1, "\n", 1);
	free_dict(dict, size);
	return (0);
}
