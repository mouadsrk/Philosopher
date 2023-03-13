#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_data
{
    pthread_mutex_t mutex;
    pthread_t th;
    struct s_data *next;
    int mails;
} t_data;



t_data	*stnew()
{
	t_data	*s;

	s = malloc (sizeof(t_data));
	if (s == NULL)
		return (NULL);
    s->mails = 0;
	s->next = NULL;
	return (s);
}







void *routine(void *  tata)
{
    t_data *data;

    data = (t_data *) tata;
    int i = 0;
    while(i < 1000000)
    {
        pthread_mutex_lock(&data->mutex);
        i++;
        data->mails++;
        pthread_mutex_unlock(&data->mutex);
    }
    return NULL;
}

int main() 
{
    t_data *data;
    data = stnew();
    data->next= stnew();
    pthread_mutex_init(&data->mutex, NULL);
    pthread_mutex_init(&data->next->mutex, NULL);
    pthread_create(&data->th, NULL,&routine,data);
    pthread_create(&data->next->th, NULL,&routine, data->next);
    pthread_join(data->th,NULL);
    pthread_join(data->next->th,NULL);
    pthread_mutex_destroy(&data->mutex);
    pthread_mutex_destroy(&data->next->mutex);
    printf("NUMBER of mails: %d \n",data->mails);
    printf("NUMBER of mails2: %d \n",data->next->mails);
}
