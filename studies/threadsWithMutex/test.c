#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct	s_main
{
	int	size;
	char	*s;
}		t_main;

void	*func(void *s)
{
	printf("thread is printing :%s:\n", (char *)s);
	return (NULL);
}

void	*func2(void *s)
{
	//usleep(250000);
	printf("thread is printing :%s:\n", (char *)s);
	return (NULL);
}

void	*show(void *ptr) //esse ponteiro vai ser derreferenciado dentro do escopo dessa func.
{
	t_main	*new; //criamos um ponteiro para conseguir acessar a struct atraves do void ptr.
	int	i;

	new = (t_main *)ptr; //nosso ponteiro new aponta para o ponteiro ptr, ja derreferenciado.
			     //dessa forma, conseguimos manipular o conteudo da struct que foi passada 
			     //quando criamos a nova thread.
	i = 1;
	while (i <= new->size)
	{
		printf("-> :%s:\n", new->s);
		printf(" %i, ", i);
		i++;
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;
	t_main		m1;
	t_main		m2;

	m1.size = 10;
	m1.s = "allan";

	m2.size = 5;
	m2.s = "prado";
	//char	*s = "allan prado";
	//char	a[5] = "allan";

	printf("-------- Using threads --------\n");

//	pthread_create(&t1, NULL, func2, (void*)s);
//	pthread_join(t1, NULL);
//	pthread_create(&t2, NULL, func, (void*)a);
//	pthread_join(t2, NULL);

	pthread_create(&t1, NULL, show, (void*)&m1); //Criando uma nova thread
	pthread_join(t1, NULL); // fazendo a thread main esperar a thread t1 terminar de executar
	pthread_create(&t2, NULL, show, (void*)&m2); //Criando uma nova thread
	//pthread_join(t1, NULL);
	pthread_join(t2, NULL); // fazendo a thread main esperar a thread t2 terminar de executar

	printf("-------- Using threads --------\n");

	return (1);
}
