/* 
 * This file is part of the UCB release of Plan 9. It is subject to the license
 * terms in the LICENSE file found in the top-level directory of this
 * distribution and at http://akaros.cs.berkeley.edu/files/Plan9License. No
 * part of the UCB release of Plan 9, including this file, may be copied,
 * modified, propagated, or distributed except according to the terms contained
 * in the LICENSE file.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void
main(int argc, char **argv)
{
	char *f, *b, *s;
	int n;

	if(argc < 2 || argc > 3){
		fprintf(stderr, "Usage: basename string [suffix]\n");
		exit(1);
	}
	s = argv[1];
	b = s + strlen(s) - 1;
	while(b > s && *b == '/')
		b--;
	*++b = 0;
	if(b == s+1 && s[0] == '/') {
		printf("/");
		exit(0);
	}
	/* now b is after last char of string, trailing slashes removed */

	for(f = b; f >= s; f--)
		if(*f == '/'){
			f++;
			break;
		}
	if(f < s)
		f = s;

	/* now f is first char after last remaining slash, or first char */

	if(argc == 3){
		n = strlen(argv[2]);
		if(n < b-f && strncmp(b-n, argv[2], n) == 0){
			b -= n;
			*b = 0;
		}
	}
	printf("%s\n", f);
	exit(0);
}
