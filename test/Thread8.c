#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include <stdio.h>
#include <pthread.h>

#define ARRSIZE 80000000
int x[ARRSIZE];
struct tms tmsstart, tmsend;
clock_t start, end;
// другие глобальные переменные...
int res1, res2, res3, res4;
int startind1 = 0, startind2 = ARRSIZE / 4, startind3 = ARRSIZE / 2, startind4 = ARRSIZE - ARRSIZE / 4;
pthread_mutex_t m;

void err_thr(int err, const char *info)
{
	printf("%s (%d)\n", info, err);
	exit(1);
}
double sec(long ticks)
{
	return (double)ticks / sysconf(_SC_CLK_TCK);
}
void printtime(const char *info)
{
	/*printf("%s: realtime - %.2f, usertime - %.2f, sys time - %.2f\n",
		   info, sec(end - start),
		   sec(tmsend.tms_utime - tmsstart.tms_utime),
		   sec(tmsend.tms_stime - tmsstart.tms_stime));
	*/
	printf("%s: realtime - %.2f\n",
		   info, sec(end - start));
}
void alg1(char const *argv[])
{
	srand(atoi(argv[1]));
	for (int j = 0; j < ARRSIZE; j++)
		x[j] = rand() % 201 - 100;
	start = times(&tmsstart);
	// реализация алгоритма 1...
	for (int i = 0; i < ARRSIZE; i++)
	{
		if (x[i] > 0)
			res1 += 1;
	}
	end = times(&tmsend);
	// вывод полученных результатов...
	printf("res = %d\n", res1);
	printtime("No threads");
}
void *thr_sum_no_mutex(void *arg)
{
	int st = *(int *)arg;
	for (int i = st; i < st + ARRSIZE / 4; i++)
	{
		if (x[i] > 0)
			res2 += 1;
	}
	return (void *)0;
}
void alg2()
{
	start = times(&tmsstart);
	// реализация алгоритма 3...
	int err;

	pthread_t tid1, tid2, tid3, tid4;
	err = pthread_create(&tid1, NULL, thr_sum_no_mutex, &startind1);
	if (err != 0)
		err_thr(err, "cannot create thread 1");
	err = pthread_create(&tid2, NULL, thr_sum_no_mutex, &startind2);
	if (err != 0)
		err_thr(err, "cannot create thread 2");
	err = pthread_create(&tid3, NULL, thr_sum_no_mutex, &startind3);
	if (err != 0)
		err_thr(err, "cannot create thread 3");
	err = pthread_create(&tid4, NULL, thr_sum_no_mutex, &startind4);
	if (err != 0)
		err_thr(err, "cannot create thread 4");
	pthread_join(tid1, 0);
	pthread_join(tid2, 0);
	pthread_join(tid3, 0);
	pthread_join(tid4, 0);

	end = times(&tmsend);
	// вывод полученных результатов...
	printf("res = %d\n", res2);
	printtime("No mutex");
}
void *thr_sum_mutex_inside(void *arg)
{
	int st = *(int *)arg;
	for (int i = st; i < st + ARRSIZE / 4; i++)
	{
		if (x[i] > 0)
		{
			if (pthread_mutex_lock(&m) == 0)
			{
				res3 += 1;
				pthread_mutex_unlock(&m);
			}
		}
	}
	return (void *)0;
}
void alg3(char const *argv[])
{
	srand(atoi(argv[2]));
	for (int j = 0; j < ARRSIZE; j++)
		x[j] = rand() % 201 - 100;
	start = times(&tmsstart);
	// реализация алгоритма 4...
	int err = pthread_mutex_init(&m, 0);
	if (err != 0)
		err_thr(err, "cannot create mutex");

	pthread_t tid1, tid2, tid3, tid4;
	err = pthread_create(&tid1, NULL, thr_sum_mutex_inside, &startind1);
	if (err != 0)
		err_thr(err, "cannot create thread 1");
	err = pthread_create(&tid2, NULL, thr_sum_mutex_inside, &startind2);
	if (err != 0)
		err_thr(err, "cannot create thread 2");
	err = pthread_create(&tid3, NULL, thr_sum_mutex_inside, &startind3);
	if (err != 0)
		err_thr(err, "cannot create thread 3");
	err = pthread_create(&tid4, NULL, thr_sum_mutex_inside, &startind4);
	if (err != 0)
		err_thr(err, "cannot create thread 4");

	pthread_join(tid1, 0);
	pthread_join(tid2, 0);
	pthread_join(tid3, 0);
	pthread_join(tid4, 0);

	end = times(&tmsend);
	// вывод полученных результатов...
	printf("res = %d\n", res3);
	printtime("Mutex inside loop");
}
void *thr_sum_mutex_outside(void *arg)
{
	int st = *(int *)arg;
	double res0 = 0;
	for (int i = st; i < st + ARRSIZE / 4; i++)
	{
		if (x[i] > 0)
		{
			res0 += 1;
		}
	}
	if (pthread_mutex_lock(&m) == 0)
	{
		res4 += res0;
		pthread_mutex_unlock(&m);
	}
	return (void *)0;
}
void alg4(char const *argv[])
{
	srand(atoi(argv[3]));
	for (int j = 0; j < ARRSIZE; j++)
		x[j] = rand() % 201 - 100;
	start = times(&tmsstart);
	// реализация алгоритма 1...
	int err = pthread_mutex_init(&m, 0);
	if (err != 0)
		err_thr(err, "cannot create mutex");

	pthread_t tid1, tid2, tid3, tid4;
	err = pthread_create(&tid1, NULL, thr_sum_mutex_outside, &startind1);
	if (err != 0)
		err_thr(err, "cannot create thread 1");
	err = pthread_create(&tid2, NULL, thr_sum_mutex_outside, &startind2);
	if (err != 0)
		err_thr(err, "cannot create thread 2");
	err = pthread_create(&tid3, NULL, thr_sum_mutex_outside, &startind3);
	if (err != 0)
		err_thr(err, "cannot create thread 3");
	err = pthread_create(&tid4, NULL, thr_sum_mutex_outside, &startind4);
	if (err != 0)
		err_thr(err, "cannot create thread 4");

	pthread_join(tid1, 0);
	pthread_join(tid2, 0);
	pthread_join(tid3, 0);
	pthread_join(tid4, 0);
	end = times(&tmsend);
	// вывод полученных результатов...
	printf("res = %d\n", res4);
	printtime("Mutex outside loop");
}
int main(int argc, char const *argv[])
{
	alg1(argv);
	// alg2();
	alg3(argv);
	alg4(argv);
	return 0;
}