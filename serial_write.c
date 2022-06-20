#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <termio.h>
#include <string.h>

#include <time.h>
#include <stdio.h>

int main(void){
	int fd;
	fd = open("/dev/ttyO1", O_RDWR | O_NOCTTY);

	assert(fd != -1);

	struct termios newtio;


	time_t start = time(NULL);
	time_t end = time(NULL);
	while(end-start < 30){
		end = time(NULL);

	memset(&newtio, 0, sizeof(newtio));
	newtio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR | ICRNL;
	newtio.c_oflag = 0;
	newtio.c_lflag = ~(ICANON | ECHO | ECHOE | ISIG);
//	newtio.c_lflag = 0;

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &newtio);

	const char *str = "abcd";
//	unsigned char str[] = {'A', 'B'};
//	char str[] = {0x01, 0x02, 0x03, 0x04};

	write(fd, str, strlen(str)+1);
//	printf("len: %d\n", strlen(str));
//	sleep(2);
	usleep(100000);
	}
	close(fd);
	return 0;
}
