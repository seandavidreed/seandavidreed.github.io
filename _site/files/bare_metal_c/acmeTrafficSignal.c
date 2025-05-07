/*
 * acmeTrafficSignal.c
 *
 *  Created on: Feb 15, 2023
 *      Author: seandavidreed
 */

#include <stdio.h>
#include <stdint.h>

struct LIGHT {
	uint8_t stateChange;
};

struct DIRECTION {
	uint8_t relayPower;
};

struct SLEEP {
	uint8_t seconds;
};

enum commandIDs {
	LIGHT, DIRECTION, SLEEP
};

struct COMMAND {
	enum commandIDs commandID;
	union {
		struct LIGHT light;
		struct DIRECTION direction;
		struct SLEEP sleep;
	} command;
};

void light(struct LIGHT command) {
	switch (command.stateChange) {
		case 1:
			printf("Set STOP to OFF\n");
			break;
		case 2:
			printf("Set STOP to ON\n");
			break;
		case 4:
			printf("Set GO to OFF\n");
			break;
		case 8:
			printf("Set GO to ON\n");
	}
}

void direction(struct DIRECTION command) {
	if (command.relayPower)
		printf("Set DIRECTION to ON\n");
	else
		printf("Set DIRECTION to OFF\n");
}

void sleep(struct SLEEP command) {
	printf("SLEEP for %d seconds", command.seconds);
}

void issueCommand(struct COMMAND Command) {
	void (*funcPtr[])() = {light, direction, sleep};
	funcPtr[Command.commandID](Command.command);
}

int main() {
	struct COMMAND myCommand = {
		.commandID = LIGHT,
		.command.light.stateChange = 0b00001000
	};

	issueCommand(myCommand);

	myCommand.commandID = DIRECTION;
	myCommand.command.direction.relayPower = 1;

	issueCommand(myCommand);

	myCommand.commandID = SLEEP;
	myCommand.command.sleep.seconds = 230;

	issueCommand(myCommand);

	return 0;
}
