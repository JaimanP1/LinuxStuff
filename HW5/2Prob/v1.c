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
				printf("option f value: %s\n", optarg); 
				break;
			case 's': 
				printf("option s value: %s\n", optarg);
				break;
			case '?':
				printf("unkown option: %c\n", optopt);
				break;
			case ':': 
				printf("option %c needs a value\n", optopt);
				break;
			default:
				printf("something went wrong");
				return 0;

		}
	}
	if (optind < argc) {
		printf("Remaining arguments:\n");
		while (optind < argc) {
		       	printf("  %s\n", argv[optind++]);
		}
	}
}
