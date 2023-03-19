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

long time_now(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}


int main() 
{
    struct timeval tv;
    long begin , now;
    int i;
    i = 0;
    begin = time_now();
    printf("%ld\n",begin);
    usleep(100 * 1000);
    usleep(100 * 1000);
    usleep(100 * 1000);
    usleep(100 * 1000);
    usleep(100 * 1000);
    usleep(100 * 1000);
    usleep(100 * 1000);
    now = time_now() - begin;
    printf("%ld\n",now);
    // // usleep(4000);
    // now = time_now() ;
    // printf("%ld\n",now);
    

}
