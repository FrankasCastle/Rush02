/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush_nb_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucsanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 09:02:52 by lucsanto          #+#    #+#             */
/*   Updated: 2026/03/14 09:02:54 by lucsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**get_units(void)
{
	static char	*units[] = {"zero", "one", "two", "three", "four", "five",
		"six", "seven", "eight", "nine"};

	return (units);
}
char	**get_teens(void)
{
	static char	*teens [] = {"", "eleven", "twelve", "thirteen", "fourteen",
		"fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

	return (teens);
}
char	**get_tens(void)
{
	static char	*tens [] = {"", "ten", "twenty", "thirty", "forty", "fifity", "sixty", "seventy",
		"eighty", "ninety"};

	return (tens);
}
char	**get_larger_nbs(void)
{
	static char	*larger_nbs [] = {"hundred", "thousand", "million", "billion", "trillion",
		"quadrillion", "quintillion", "sextillion", "septillion", "octillion", "decillion",
		"undecillion"};

	return (larger_nbs);
}
char	**get_groups(void)
{
	static char	*groups [] = {"000", "000", "000", "000", "000", "000", "000",
		"000", "000", "000", "000"};

	return (groups);
}

void	group_aloctator(char *str, char *groups[11][4])
{
	int group_index;
	int string_index;
	int rec_str_index;
	int aux_counter;
	
	group_index = 11;
	string_index = 2;
	rec_str_index = 0;
	while (str[rec_str_index] != '\0')
	{
		rec_str_index++;
	}
	while (rec_str_index > 0)
	{
		rec_str_index--;
		groups[group_index][string_index] = str[rec_str_index];
		string_index--;
		if (string_index == 0)
		{
			groups[group_index][string_index] = str[rec_str_index];
			string_index = 2;
			group_index--;
		}
	}
}
//21 tamanho maximo string recebida

void	number_translator(char *str)
{
	int	c;
	int	d;
	int	u;
	int	du;

	c = str[0] - '0';
	d = str[1] - '0';
	u = str[2] - '0';
	du = (d * 10) + u;
	if (c > 0)
	{
		if (du > 10 && du < 20)
		{
			strcat_hundred_specials(c, du - 10);
			return ;
		}
		strcat_hundred(c, d, u);
	}
	else
	{
		if (du > 10 && du < 20)
		{
			strcat_specials(du - 10);
			return ;
		}
		strcat_flat(d, u);
	}
}

void	strcat_flat(int d, int u)
{
	int		i;
	int		j;
	char	**tens;
	char	**units;

	tens = get_tens();
	units = get_units();
	if (d > 0)
	{
		j = d;
		i = 0;
		while (tens[j][i] != '\0')
		{
			write(1, &tens[j][i], 1);
			i++;
		}
		if (u > 0)
			write(1, " ", 1);
	}
	if (u > 0)
	{
		j = u;
		i = 0;
		while (units[j][i] != '\0')
		{
			write(1, &units[j][i], 1);
			i++;
		}
	}
}

void	strcat_specials(int du)
{
	int		j;
	int		i;
	char	**teens;

	j = du;
	i = 0;
	teens = get_teens();
	while (teens[j][i] != '\0')
	{
		write(1, &teens[j][i], 1);
		i++;
	}
}

void	strcat_hundred(int c, int d, int u)
{
	int		i;
	int		j;
	char	**units;
	char	**tens;

	units = get_units();
	tens = get_tens();
	j = c;
	i = 0;
	while (units[j][i] != '\0')
	{
		write(1, &units[j][i], 1);
		i++;
	}
	write(1, " hundred", 8);
	if (d > 0 || u > 0)
		write(1, " ", 1);
	if (d > 0)
	{
		j = d;
		i = 0;
		while (tens[j][i] != '\0')
		{
			write(1, &tens[j][i], 1);
			i++;
		}
		if (u > 0)
			write(1, " ", 1);
	}
	if (u > 0)
	{
		j = u;
		i = 0;
		while (units[j][i] != '\0')
		{
			write(1, &units[j][i], 1);
			i++;
		}
	}
}

void	strcat_hundred_specials(int c, int du)
{
	int		i;
	int		j;
	char	**units;
	char	**teens;

	units = get_units();
	teens = get_teens();
	j = c;
	i = 0;
	while (units[j][i] != '\0')
	{
		write(1, &units[j][i], 1);
		i++;
	}
	write(1, " hundred ", 9);
	j = du;
	i = 0;
	while (teens[j][i] != '\0')
	{
		write(1, &teens[j][i], 1);
		i++;
	}
}

void	wich_index(int larger_index)
{
	int i;

	i = larger_index;
	if (i = 0)
		write (1, "undecillion", 12);
	else if (i = 1)
		write (1, "decillion", 10);
	else if (i = 2)
		write (1, "octillion", 10);
	else if (i = 3)
		write (1, "septillion", 11);
	else if (i = 4)
		write (1, "sextillion", 11);
	else if (i = 5)
		write (1, "quintillion", 12);
	else if (i = 6)
		write (1, "quadrillion", 12);
	else if (i = 7)
		write (1, "trillion", 9);
	else if (i = 8)
		write (1, "billion", 8);
	else if (i = 9)
		write (1,"million", 8);
	else if (i = 10)
		write (1, "thousand", 9);
}


// indices: 
// 11 = hundred
// 10 = thousand
// 9 = million
// 8 = billion
// 7 = trillion
// 6 = quadrillion
// 5 = quintillion
// 4 = sextillion
// 3 = septillion
// 2 = octillion
// 1 = decillion
// 0 = undeccillion