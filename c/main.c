#include <stdio.h>
unsigned short p = 0; unsigned char t[65536], c[65536];
int main(int a, char *v[]){ FILE *f = fopen(a > 1 ? v[1] : "code.bf", "r");
if (!f || ( fread(c, 1, sizeof(c) - 1, f), fclose(f) )) return 1;
for (unsigned char *i = c; *i != '\0'; i++) { int d = 1; switch (*i) {
case '>':   p++;            break; case '<':   p--;              break;
case '+': t[p]++;           break; case '-': t[p]--;             break;
case ',': t[p] = getchar(); break; case '.': putchar(t[p]);      break;
case '[': if(!t[p]){ while(d){ i++; d += (*i=='[')-(*i==']'); }} break;
case ']': if( t[p]){ while(d){ i--; d += (*i==']')-(*i=='['); }} break; }}}