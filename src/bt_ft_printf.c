/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_ft_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaniele <hdaniele@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:01:12 by hdaniele          #+#    #+#             */
/*   Updated: 2023/04/15 12:07:40 by hdaniele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		i;
	int		ret;

	va_start(arg, format);
	i = 0;
	ret = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			ret += search(format[i + 1], arg);
			i += 2;
		}
		else
		{
			ret += ft_putchar(format[i]);
			i++;
		}
	}
	return (ret);
}

int	search(char format, va_list arg)
{
	int	ret;

	ret = 0;
	if (format == 'i' || format == 'd')
		ret += ft_putnbr(va_arg(arg, int));
	else if (format == 's')
		ret += ft_putstr(va_arg(arg, char *));
	else if (format == '%')
		ret += ft_putchar('%');
	else if (format == 'c')
		ret += ft_putchar(va_arg(arg, unsigned int));
	else if (format == 'u')
		ret += ft_putnbru(va_arg(arg, unsigned int));
	else if (format == 'p')
		ret += pointer(va_arg(arg, unsigned long));
	else if (format == 'X')
		ret += dex(va_arg(arg, unsigned int), 0, 0);
	else if (format == 'x')
		ret += dexs(va_arg(arg, unsigned int), 0, 0);
	return (ret);
}
