/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucsanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 10:18:16 by lucsanto          #+#    #+#             */
/*   Updated: 2026/03/15 10:18:18 by lucsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_dict
{
	char	*key;
	char	*value;
}	t_dict;

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

void	init_groups(char groups[11][4])
{
	int	i;

	i = 0;
	while (i < 11)
	{
		groups[i][0] = '0';
		groups[i][1] = '0';
		groups[i][2] = '0';
		groups[i][3] = '\0';
		i++;
	}
}

void	fill_groups(char *str, char groups[11][4])
{
	int	group;
	int	position_group;
	int	i;

	group = 10;
	position_group = 2;
	i = ft_strlen(str) - 1;
	while (i >= 0 && group >= 0)
	{
		groups[group][position_group] = str[i];
		position_group--;
		if (position_group < 0)
		{
			position_group = 2;
			group--;
		}
		i--;
	}
}

int	is_zero_group(char group[4])
{
	if (group[0] == '0' && group[1] == '0' && group[2] == '0')
		return (1);
	return (0);
}

void	print_scale_by_position(int position_group, t_dict *dict, int size)
{
	char	*scales[11];
	int		i;

	scales[0] = "1000000000000000000000000000000";
	scales[1] = "1000000000000000000000000000";
	scales[2] = "1000000000000000000000000";
	scales[3] = "1000000000000000000000";
	scales[4] = "1000000000000000000";
	scales[5] = "1000000000000000";
	scales[6] = "1000000000000";
	scales[7] = "1000000000";
	scales[8] = "1000000";
	scales[9] = "1000";
	scales[10] = "";
	i = 0;
	while (position_group < 10 && i < size)
	{
		if (ft_strcmp(dict[i].key, scales[position_group]) == 0)
			return (ft_putstr(dict[i].value));
		i++;
	}
}

void	translate_full_number(char *str, t_dict *dict, int size)
{
	char	groups[11][4];
	int		i;
	int		printed;

	init_groups(groups);
	fill_groups(str, groups);
	i = -1;
	printed = 0;
	while (++i < 11)
	{
		if (is_zero_group(groups[i]) == 0)
		{
			if (printed == 1)
				write(1, " ", 1);
			number_translator(groups[i], dict, size);
			if (i < 10)
			{
				write(1, " ", 1);
				print_scale_by_position(i, dict, size);
			}
			printed = 1;
		}
	}
	if (printed == 0)
		number_translator("000", dict, size);
}
