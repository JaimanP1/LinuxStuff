void *computation(void *id){

	long *myid = (long *)id;
	long sum;
	for(int i = 0; i < 1000000000; i++){
		sum += *myid;
	}
}

int main(){

	int value1 = 1, value2 = 2, value3 = 3, value4 = 4;
	
	computation((void *)&value1);
	computation((void *)&value2);
	computation((void *)&value3);
	computation((void *)&value4);

}
