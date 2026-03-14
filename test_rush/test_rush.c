#include <unistd.h>

char	**get_units(void)
{
	static char	*units[] = {"zero", "one", "two", "three", "four", "five",
		"six", "seven", "eight", "nine"};

	return (units);
}

char	**get_teens(void)
{
	static char	*teens[] = {"", "eleven", "twelve", "thirteen", "fourteen",
		"fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

	return (teens);
}

char	**get_tens(void)
{
	static char	*tens[] = {"", "ten", "twenty", "thirty", "forty", "fifty",
		"sixty", "seventy", "eighty", "ninety"};

	return (tens);
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

int	main(void)
{
	char	string[] = "112";

	number_translator(string);
	write(1, "\n", 1);
	return (0);
}