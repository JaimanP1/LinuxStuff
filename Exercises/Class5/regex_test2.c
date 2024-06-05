#include<stdio.h>
#include<stdlib.h>
#include<regex.h>

int main(){
	regex_t regex;
	char *pattern = "a.*e"; 
	char *string = "example@njit.edu";

	int result;
	result = regcomp(&regex, pattern, REG_EXTENDED);
	result = regexec(&regex, string, 0, NULL, 0);

	if(!result){
		printf("match successful");
	}
	else if (result == REG_NOMATCH){
		printf("no match found");
	}
	else{
		char error_message[100];
		regerror(result, &regex, error_message, sizeof(error_message));
	}
	return 0;
}
