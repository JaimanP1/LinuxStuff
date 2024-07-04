#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main( int argc, char **argv){
	int opt;
	while((opt=getopt(argc, argv, "cduf:s:")) != -1){
		switch(opt){
			case 'c':
			case 'd':
			case 'u':
				printf("option: %c\n", opt);
				break;
			case 'f':


		}
	}
}
