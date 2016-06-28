

char*s = "hello";
char sar[] = "hello";
char content[32];

int main(int argc, char*argv[]) {
	char psar[] = "parhello";
	char*ps = "phello";
	content[0] = 1;
	sar[3] = 1; // OK
	// sar++; // not allowed
	// s[2] = 1; // segmentation fault
	s = sar;
	s[2] = 1; // OK
	psar[3] = 1; // OK
	// ps[2] = 1; // segmentation fault
	ps = psar;
	ps[2] = 1; // OK
	return 0;
}
