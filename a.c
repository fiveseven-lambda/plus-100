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
	printf("fnc(3) = %d\n", ((int(*)(int))map)(3));
	printf("fnc(10) = %d\n", ((int(*)(int))map)(10));
	printf("fnc(520) = %d\n", ((int(*)(int))map)(520));
	close(fd);
	munmap(map, sizeof fnc);
	return 0;
}
