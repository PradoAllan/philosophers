#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

int	main(void)
{
	int	i = 1;
	struct timeval	time;

	while (i <= 20)
	{
		gettimeofday(&time, NULL);
		printf("Seconds-> %ld, microseconds-> %ld.\n", time.tv_sec, time.tv_usec);
		usleep(10000000);
		i++;
	}
	return (1);
}
