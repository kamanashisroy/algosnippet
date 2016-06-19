

char*s = "hello";
char sar[] = "hello";
char content[32];

int main(int argc, char*argv[]) {
	char*ps = "phello";
	content[0] = 1;
	sar[3] = 1;
	// sar++; // not allowed
	// s[2] = 1; // segmentation fault
	return 0;
}
