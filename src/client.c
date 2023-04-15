/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdaniele <hdaniele@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:01:02 by hdaniele          #+#    #+#             */
/*   Updated: 2023/04/15 12:04:50 by hdaniele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <signal.h>

int	g_bit;

void	received(int sig)
{
	if (sig == SIGUSR1)
		g_bit++;
	else if (sig == SIGUSR2)
	{
		g_bit++;
		ft_printf("letter sent! letter number = %i", g_bit / 8);
	}
	else
	{
		ft_printf("\tError: Invalid Signal");
		exit(22);
	}
}

int	check_pid_digits(char *pid)
{
	int	i;

	i = 0;
	while (pid[i])
	{
		if (ft_isdigit(pid[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

void	sendbit(pid_t pid, char *message)
{
	int	i;
	int	bit_comp;
	int	shift_bits;

	bit_comp = 0;
	i = 0;
	while (message[i])
	{
		shift_bits = 0;
		while (shift_bits < 8)
		{
			while (g_bit != bit_comp)
				usleep(1);
			if ((message[i] >> shift_bits) & 0b00000001)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit_comp++;
			shift_bits++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	g_bit = 0;
	signal(SIGUSR1, received);
	signal(SIGUSR2, received);
	if (argc != 3)
	{
		ft_printf("Wrong number of arguments!");
		exit(0);
	}
	if (check_pid_digits(argv[1]) || ft_strlen(argv[1]) > 7)
		ft_printf("Error: PID\n");
	pid = ft_atoi(argv[1]);
	sendbit(pid, ft_strjoin(argv[2], "\n"));
	return (0);
}
