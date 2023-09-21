#include <stdio.h>

int	check_cometes(char *str)
{
	int		i;
	int		coma;
	int		flag;

	i = 0;
	coma = 0;
	flag = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && flag == 0)
		{
			coma = str[i];
			flag = 1;
		}
		if (coma == str[i] && flag == 1)
		{
			flag = 0;
		}
		// else
		// 	return (coma);
		i++;
	}
	return (flag);
}

int main(int ac, char **av)
{
	int res;

	res = 0;
	if (ac == 2)
	{
		res = check_cometes(av[1]);
		printf("res = %i\n", res);
		if (res == 1 || res == 34 || res == 39)
			printf("ERROR %i\n", res);
	} else {
		printf("Muchos argumentos\n");
	}
	return (0);
}