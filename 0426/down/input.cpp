#include <cstdio>
#include <cctype>

inline char getc() {
	static char *p1, *p2, buf[1<<20];
	return p1 == p2 ? (p2 = (p1 = buf) + fread(buf, 1, 1<<20, stdin), p1 == p2 ? 10 : *p1++) : *p1++;
}

inline int read() {
	int f = 1, r = 0; char c = getc();
	while (!isdigit(c)) f ^= c == '-', c = getc();
	while (isdigit(c)) r = r * 10 + c - 48, c = getc();
	return f ? r : -r;
}

int main() {
	
	return 0;
}
