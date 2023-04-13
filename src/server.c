#include <signal.h>
#include <unistd.h>
#include "./libft.h"

char g_char = 0;

void byte_reader(int sbit, siginfo_t *siginfo, void *context)
{
	static int ctr = 0;
	
	(void)context;
	if (sbit == SIGUSR1)
		g_char += (1<<ctr);
	if (ctr == 7)
	{
		write(1, &g_char, 1);
		g_char = 0;
		ctr = 0;
		kill(siginfo->si_pid, SIGUSR2);
		return ;
	}
	ctr++;
	kill(siginfo->si_pid, SIGUSR1);
}

int main(void)
{
	struct sigaction	s_sa;
	sigset_t	sigset;
	int			pid;

	pid = getpid();
	sigemptyset(&sigset);
	s_sa.sa_handler = NULL;
	s_sa.sa_mask = sigset;
	s_sa.sa_flags = SA_SIGINFO;
	s_sa.sa_sigaction = byte_reader;
	sigaddset(&sigset, SIGUSR1);
	sigaddset(&sigset, SIGUSR2);
	sigaction(SIGUSR1, &s_sa, NULL);
	sigaction(SIGUSR2, &s_sa, NULL);
	ft_printf("PID: %d\n", pid);
	while(1)
	{
		pause();
	}
}