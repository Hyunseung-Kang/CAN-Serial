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

int main(int argc, char **argv)
{
	int s, i;
	int nbytes;
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame;

	printf("CAN Sockets Receive Demo\r\n");

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
		nbytes = read(s, &frame, sizeof(struct can_frame));

	 	if (nbytes < 0) {
			perror("Read");
			return 1;
		}

	// dlc means size of buffer
		printf("========= TURCK CCM CAN INTERFACE TEST =========\n");
		printf("0x%03X [%d] ",frame.can_id, frame.can_dlc);
		for (i = 0; i < frame.can_dlc; i++)
			printf("%02X ",frame.data[i]);
		printf("\r\n");
		printf("ID: %d, DLC: %d ", frame.can_id, frame.can_dlc);
		printf("Data: ");
		for(i=0; i<frame.can_dlc; i++){
			if(i==2 | i==4)
				printf(":");
			printf(" %c", frame.data[i]);
		}
		printf("\n\n\n");
		end = time(NULL);
	}
	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	return 0;
}
