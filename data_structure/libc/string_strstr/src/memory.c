
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>

inline static const char* my_strstr(const char*const str, const char const*p/*pattern*/) {
	assert(str);
	assert(p);
	size_t str_len = 0;
	size_t p_len = 0;
	size_t i = 0, j = 0;
	uint8_t found = 0;
	
	while(str[str_len++]); // get string len
	str_len--;
	while(p[p_len++]); // get pattern len
	p_len--;
	
	for(i = 0; i < (str_len - p_len+1); i++) {
		found = 1;
		for(j = 0; j < p_len; j++) {
			if(str[i+j] != p[j]) {
				found = 0;
				break;
			}
		}
		if(found)
			return (str+i);
	}
	return NULL;
}

inline static void build_pattern_matrix(const char const*p, size_t p_len, long long*pmat) {
	size_t i = 0;
	size_t mp = 0;
	pmat[0] = -1;
	printf("\tmatrix for [%s] = ", p);
	printf("%lld,", pmat[0]);
	for(i = 1; i < p_len; i++) {
		if(p[i] != p[mp]) {
			pmat[i] = -1;
			printf("%lld,", pmat[i]);
			mp = 0;
			continue;
		}
		pmat[i] = pmat[i-1] + 1;
		assert(pmat[i] == mp);
		mp++;
		printf("%lld,", pmat[i]);
	}
	printf("\n");
	
}

inline static const char* my_strstr_opt(const char*const str, const char const*p/*pattern*/) {
	assert(str);
	assert(p);
	size_t str_len = 0;
	size_t p_len = 0;
	const char*ret = NULL;
	long long i = 0, j = 0;
	uint8_t found = 0;
	
	while(str[str_len++]); // get string len
	str_len--;
	while(p[p_len++]); // get pattern len
	p_len--;

	long long*pmat = malloc(p_len*sizeof(long long));
	assert(pmat);
	build_pattern_matrix(p, p_len, pmat);
	
	do {
		j = 0;
		for(i = 0;i < (str_len - p_len+1); i++) {
			found = 1;
			for(; j < p_len; j++) {
				if(str[i+j] != p[j]) {
					found = 0;
					break;
				}
			}
			if(found) {
				ret = (str+i);
				break;
			}
			if(j != 0 && pmat[j] != -1) {
				i += j;
				j = pmat[j]+1;
				printf("[%s] submatch %lld after mismatch at %lld\n", str, j+1, i);
			} else {
				if(j != 0) {
					i += j;
					printf("[%s] skipped %lld after mismatch at %lld\n", str, j+1, i);
				}
				j = 0;
			}
		}
	} while(0);
	free(pmat);
	return ret;
}



int main(int argc, char*argv[]) {
	const char*match = NULL;
	const char*str = "ababab";
	char pat[32];
	int slen = strlen(str);
	int i = 0, j = 0;
	for(i = 0; i < slen; i++) {
		for(j = 1; j < (slen - i); j++) {
			memcpy(pat, str+i, j);
			pat[j] = '\0';
			//printf(" searching: %s, in %s\n", pat, str);
			assert((match = my_strstr(str, pat)));
			assert((match = my_strstr_opt(str, pat)));
			//printf(" value: %s\n", match);
		}
	}
	strcpy(pat, "abac");
	assert(my_strstr_opt(str, pat) == NULL);
	strcpy(pat, "abab");
	str = "abcaabccabbababag";
	assert(my_strstr_opt(str, pat) != NULL);
	printf("Successful\n");
	return 0;
}
