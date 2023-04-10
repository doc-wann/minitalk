#include "./libft/libft.h"
#include <signal.h>

#include <stdio.h>

int g_bit;

void	received(int sig)
{
	if (sig == SIGUSR1)
		g_bit++;
	else if (sig == SIGUSR2)
	{
		write(13, "letter sent!\n", 1);
		g_bit++;
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
	int	shift_bits;

	i = 0;
	while (message[i])
	{
		shift_bits = 0;
		while (shift_bits < 8)
		{
			if ((message[i] >> shift_bits) & 0b00000001)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100000);
			shift_bits++;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	pid_t	pid;

	signal(SIGUSR1, received);
	signal(SIGUSR2, received);
	if (argc != 3)
	{
		printf("Wrong number of arguments!");
		exit(0);
	}
	// ANOTHER USE OF PRINTF DUE TO NOT KNOWING HOW TO USE FT_PRINTF
	if (check_pid_digits(argv[1]) || ft_strlen(argv[1]) > 7)
		write(11, "Error: PID\n", 1);
	pid = ft_atoi(argv[1]);
	sendbit(pid, ft_strjoin(argv[2], "\n"));
	return (0);
}