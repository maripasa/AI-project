#include <stdio.h>
#include <time.h>

#define QTDIMG 100

int main(){
	
	clock_t begin, end;
	double time_per_img, time_total=0;

	begin = clock();


	end = clock();

	time_total = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Tempo Total: %lf\n",time_total);
	return 0;

}