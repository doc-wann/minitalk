#include "libft.h"

int	dexs(unsigned long decimalnum, int i, int cpyresult)
{
	unsigned long	result;
	unsigned long	rest;
	char			*hexadecimal;

	result = decimalnum;
	if (decimalnum == 0)
		return (ft_putchar('0'));
	while (decimalnum != 0 && i++ > -1)
		decimalnum = decimalnum / 16;
	hexadecimal = malloc(sizeof(char) * i + 1);
	hexadecimal[i--] = '\0';
	while (result != 0)
	{
		rest = result % 16;
		if (rest < 10)
			hexadecimal[i] = (48 + rest);
		else
			hexadecimal[i] = (87 + rest);
		result = result / 16;
		i--;
	}
	cpyresult = ft_putstr(hexadecimal);
	free(hexadecimal);
	return (cpyresult);
}

int	dex(unsigned long decimalnum, int i, int cpyresult)
{
	unsigned long	result;
	unsigned long	rest;
	char			*hexadecimal;

	result = decimalnum;
	if (decimalnum == 0)
		return (ft_putchar('0'));
	while (decimalnum != 0 && i++ > -1)
		decimalnum = decimalnum / 16;
	hexadecimal = malloc(sizeof(char) * i + 1);
	hexadecimal[i--] = '\0';
	while (result != 0)
	{
		rest = result % 16;
		if (rest < 10)
			hexadecimal[i] = (48 + rest);
		else
			hexadecimal[i] = (55 + rest);
		result = result / 16;
		i--;
	}
	cpyresult = ft_putstr(hexadecimal);
	free(hexadecimal);
	return (cpyresult);
}

int	pointer(unsigned long ptr)
{
	int	ret;

	if (!ptr)
		return (ft_putstr("(nil)"));
	ret = ft_putstr("0x");
	ret += dexs(ptr, 0, 0);
	return (ret);
}
