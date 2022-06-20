#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <time.h>
#include <math.h>

int main(int argc, char **argv)
{
	int s;
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;

	printf("CAN Sockets Demo\r\n");

	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Socket");
		return 1;
	}

	time_t start = time(NULL);
	time_t end = time(NULL);

	while(end - start < 300){
		strcpy(ifr.ifr_name, "can0" );
		ioctl(s, SIOCGIFINDEX, &ifr);

		memset(&addr, 0, sizeof(addr));
		addr.can_family = AF_CAN;
		addr.can_ifindex = ifr.ifr_ifindex;

		if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
			perror("Bind");
			return 1;
		}

		frame.can_id = 0x555;
		frame.can_dlc = 8;

		struct timespec specific_time;
		struct tm*now;
		int millisec;

		clock_gettime(CLOCK_REALTIME, &specific_time);
		now = localtime(&specific_time.tv_sec);
		millisec = specific_time.tv_nsec;

		millisec = floor(specific_time.tv_nsec/1.0e6);

//	sprintf(frame.data, "TURCK[%02d/%02d] %02d:%02d:%02d::%d", now->tm_mon + 1,
//		now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, millisec);

		sprintf(frame.data, "%02d%02d%03d", now->tm_min, now->tm_sec, millisec);

		if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
			perror("Write");
			return 1;
		}
		end = time(NULL);
		usleep(100000);	// 100ms ( 100,000)
	}

	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	return 0;
}
