#include<regex.h>
#include<stdlib.h>
#include<stdio.h>

int main (void) {
	
	regex preg;
	char *string = "a very simple string";
	char *pattern = "\\(sim[a-z]le \\1";
	char buff[100];
	int rc, i;
	size_t nmatch = 2;
	regmatch_t pmatch[2];

	if (0 != (rc = regcomp(&preg, pattern, 0))) {
		regerror (rc, &preg, buf, 100);
		printf ("regcomp() failed: %d(%s)\n", rc, buf);
		exit(EXIT_FAILURE);
	}

	if (0 != (rc = regexec (&preg, string, nmatch, pmatch, 0))) {
		regerror (rc, &preg, buf, 100);
		printf ("Failed to match '%s' with '%s': %d(%s).\n", string, pattern, rc, buf);
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < nmatch; i++){
		if(pmatch[i].rm_so == -1) break;
		printf("a match \"%.*s\" is found at postion %d	to %d.\n", pmatch[i].rm_eo - pmatch[i].rm_so, &string[pmatch[i].rm_so], pmatch[i].rm_so, pmatch[i].rm_eo - 1);
	}

	regfree (&preg);
	return 0;
}
