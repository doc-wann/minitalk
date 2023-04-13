#include "./libft.h"
#include <signal.h>

#include <stdio.h>
//MUST REMOVE STDIO!!

int g_bit;


void	received(int sig)
{
	if (sig == SIGUSR1)
	{
		g_bit++;
		printf("bit sent! bit number = %i\n", g_bit);
		//this CAN BE commented; is nothing but a more precise iteration of the sigusr2 call;
	}
	else if (sig == SIGUSR2)
	{
		g_bit++;
		printf("letter sent! letter number = %i | bit = %i\n", g_bit/8, g_bit);
	}
	else
	{
		write(22, "\tError: Invalid Signal", 1);
		exit(22);
	}
}

int check_pid_digits(char *pid)
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

void sendbit(pid_t pid, char *message)
{
	int	i;
	int bit_comp;
	int	shift_bits;

	bit_comp = 0;
	i = 0;
	while (message[i])
	{
		shift_bits = 0;
		while (shift_bits < 8)
		{
			while (g_bit != bit_comp)
			{
				// printf("\n%i/%i - g_bit/bit_comp\n", g_bit, bit_comp);
				usleep(500);
				// usleep time can be reduced, but test are yet to be done. If my perception of how this code is working is right, the usleep might be set to values as low as 1. Still, this needs further testing;
				// reducing the usleep time as stated above can potentially  make this the most eficient form of UNIX signal communication :) 
			}
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

int main(int argc, char **argv)
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
