#include"stdio.h"
int main(){
	FILE *f;
	f=fopen("/sdcard/test.txt","r+");
	int time=0;
	char c;
	while (1){
		c=fgetc(f);
		if (c!='\n'){
			printf("%c_%d\n",c,c);
			time++;
		}
		if (!feof(f)){
			break;
		}
	}
	printf("time==%d\n",time);
	fclose(f);
}