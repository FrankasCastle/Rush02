#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_DICT 50

typedef struct s_dict
{
	char	*key;
	char	*value;
}	t_dict;

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	str_conv(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	return (n);
}

char	*ft_strdup_range(char *src, int start, int end)
{
	char	*dest;
	int		i;

	dest = (char *)malloc(end - start + 1);
	if (!dest)
		return (0);
	i = 0;
	while (start < end)
		dest[i++] = src[start++];
	dest[i] = '\0';
	return (dest);
}

int	get_file_size(char *filename)
{
	int		fd;
	int		bytes;
	int		total;
	char	tmp[1024];

	total = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	bytes = read(fd, tmp, 1024);
	while (bytes > 0)
	{
		total = total + bytes;
		bytes = read(fd, tmp, 1024);
	}
	close(fd);
	if (bytes < 0)
		return (-1);
	return (total);
}

char	*dict_reader(char *filename)
{
	int		fd;
	int		size;
	int		bytes;
	int		total_read;
	char	*buffer;

	size = get_file_size(filename);
	if (size < 0)
		return (NULL);
	buffer = (char *)malloc(size + 1);
	if (!buffer)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(buffer), NULL);
	total_read = 0;
	bytes = read(fd, buffer + total_read, size - total_read);
	while (bytes > 0)
	{
		total_read += bytes;
		bytes = read(fd, buffer + total_read, size - total_read);
	}
	close(fd);
	if (bytes < 0)
		return (free(buffer), NULL);
	buffer[total_read] = '\0';
	return (buffer);
}

void	skip_line_breaks(char *buffer, int *index_dict)
{
	while (buffer[*index_dict] == '\n')
		(*index_dict)++;
}

void	skip_inline_spaces(char *buffer, int *index_dict)
{
	while (buffer[*index_dict] && ft_is_space(buffer[*index_dict])
		&& buffer[*index_dict] != '\n')
		(*index_dict)++;
}

int	get_key(char *buffer, int *index_dict, t_dict *dict, int count)
{
	int	start;

	start = *index_dict;
	while (buffer[*index_dict] >= '0' && buffer[*index_dict] <= '9')
		(*index_dict)++;
	if (*index_dict == start)
		return (0);
	dict[count].key = ft_strdup_range(buffer, start, *index_dict);
	if (!dict[count].key)
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
	if (!dict[count].value)
		return (0);
	return (1);
}

int	parse_dict(char *buffer, t_dict *dict)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (buffer[i] && count < MAX_DICT)
	{
		skip_line_breaks(buffer, &i);
		skip_inline_spaces(buffer, &i);
		if (!buffer[i])
			break ;
		if (!get_key(buffer, &i, dict, count))
			break ;
		skip_inline_spaces(buffer, &i);
		if (!get_value(buffer, &i, dict, count))
			break ;
		if (buffer[i] == '\n')
			i++;
		count++;
	}
	return (count);
}

char	*ft_dict_get(int key, t_dict *dict, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (str_conv(dict[i].key) == key)
			return (dict[i].value);
		i++;
	}
	return (0);
}

void	print_dict_value(int key, t_dict *dict, int size)
{
	char	*value;

	value = ft_dict_get(key, dict, size);
	if (value)
		ft_putstr(value);
}

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
}

int	main(void)
{
	char	*buffer;
	t_dict	dict[MAX_DICT];
	int		size;

	buffer = dict_reader("numbers.dict");
	if (!buffer)
		return (write(1, "Dict Error\n", 11), 1);
	size = parse_dict(buffer, dict);
	free(buffer);
	number_translator("005", dict, size);
	write(1, "\n", 1);
	number_translator("318", dict, size);
	write(1, "\n", 1);
	number_translator("999", dict, size);
	write(1, "\n", 1);
	number_translator("100", dict, size);
	write(1, "\n", 1);
	free_dict(dict, size);
	return (0);
}