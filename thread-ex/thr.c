#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define MAIN_PARAMETER_1 1

int32_t sum;
void *runner (void *param);

int32_t main (int32_t argc, int8_t *argv[])
{
  pthread_t tid;
 // printf ("HOLA 1");
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&tid, &attr, runner, argv[MAIN_PARAMETER_1]);
  pthread_join(tid, NULL);
 // printf ("HOLA 2");
  printf("In function \nthread id = %d\n", pthread_self()); 
  printf ("sum = %d\n", sum);
}

void *runner (void *param)
{
  int32_t i = 0;
//param=param*5;
  int32_t upper = atoi (param);
 // printf ("HOLA 3");
  sum = 0;
  while (upper--)
    {
      //i++;
      sum += 5;
    }
  pthread_exit (0);
}
