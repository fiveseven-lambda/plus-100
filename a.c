#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(void){
	char fnc[] = {0x55, 0x48, 0x89, 0xe5, 0x89, 0x7d, 0xfc, 0x8b, 0x45, 0xfc, 0x83, 0xc0, 0x64, 0x5d, 0xc3};
	int fd = open("/dev/zero", O_RDWR);
	unsigned char *map = mmap(NULL, sizeof fnc, PROT_WRITE | PROT_EXEC, MAP_PRIVATE, fd, 0);
	memcpy(map, fnc, sizeof fnc);
	int a;
	scanf("%d", &a);
	printf("%d + 100 = %d\n", a, ((int(*)(int))map)(a));
	close(fd);
	munmap(map, sizeof fnc);
	return 0;
}
