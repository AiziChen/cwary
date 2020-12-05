#include <string.h>


int main(void)
{
	extern int errno;
	strerror(1);
	return 0;
}
