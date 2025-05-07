/*
 * car_struct.c
 *
 *  Created on: Feb 15, 2023
 *      Author: seandavidreed
 */

#include <stdio.h>
#include <stdint.h>

#define MAKE_LIST				\
	DEFINE_ITEM(TESLA),			\
	DEFINE_ITEM(MAZDA),			\
	DEFINE_ITEM(HONDA),			\
	DEFINE_ITEM(LEXUS),			\
	DEFINE_ITEM(TOYOTA),		\
	DEFINE_ITEM(HYUNDAI),		\
	DEFINE_ITEM(AUDI),			\
	DEFINE_ITEM(NISSAN),		\
	DEFINE_ITEM(DODGE),			\
	DEFINE_ITEM(VOLKSWAGEN),	\
	DEFINE_ITEM(KIA),			\
	DEFINE_ITEM(VOLVO),			\
	DEFINE_ITEM(ACURA),			\
	DEFINE_ITEM(CHEVROLET),		\
	DEFINE_ITEM(FORD)

#define DEFINE_ITEM(X) X
enum make {
	MAKE_LIST
};
#undef DEFINE_ITEM

#define DEFINE_ITEM(X) #X
static const char* makeNames[] = {
	MAKE_LIST
};
#undef DEFINE_ITEM

enum fuelType {
	UNLEADED, PREMIUM, SUPREME
};

struct electric {
	uint8_t chargingTime;
	uint8_t MPGe;
	uint16_t range;
};

struct gas {
	enum fuelType fuelType;
	uint8_t mpgCity;
	uint8_t mpgHighway;
	uint8_t fullTank;
};


struct car {
	uint8_t year[5];
	enum make make;
	uint8_t model[10];
	uint32_t color; // Stores the color as RGB value
	uint8_t doors;
	uint8_t seats;
	uint32_t odometer;
	union {
		struct electric electric;
		struct gas gas;
	} runType;
};

uint32_t writeColor(const uint8_t R, const uint8_t G, const uint8_t B) {
	uint32_t color = 0x0;

	// Add B value
	color |= B;
	color <<= 8;

	// Add G value
	color |= G;
	color <<= 8;

	// Add R value
	color |= R;

	return color;
}

void readColor(uint32_t color) {
	uint8_t R = 0, G = 0, B = 0;
	R = color;
	color >>= 8;
	G = color;
	color >>= 8;
	B = color;

	printf("#%x%x%x\n", R, G, B);
}

void printCar(struct car car) {
	printf("Year: %s\n", car.year);
	printf("Make: %s\n", makeNames[car.make]);
	printf("Model: %s\n", car.model);
	printf("Color: ");
	readColor(car.color);
	printf("Doors: %d\n", car.doors);
	printf("Seats: %d\n", car.seats);
	printf("Odometer: %d\n", car.odometer);

	if (car.runType.gas.mpgCity) {
		printf("Fuel Type: %d\n", car.runType.gas.fuelType);
		printf("MPG City: %d\n", car.runType.gas.mpgCity);
		printf("MPG Highway: %d\n", car.runType.gas.mpgHighway);
		printf("Tank: %d\n", car.runType.gas.fullTank);
	} else {
		printf("Charge Time: %d\n", car.runType.electric.chargingTime);
		printf("MPGe: %d\n", car.runType.electric.MPGe);
		printf("Range: %d\n", car.runType.electric.range);
	}
	puts("");
}


int main() {
	struct car car = {
		.year = "2016",
		.make = FORD,
		.model = "Escape",
		.color = writeColor(0x60, 0x68, 0x70),
		.doors = 5,
		.seats = 5,
		.odometer = 100000,
		.runType.gas = {
			.fuelType = UNLEADED,
			.mpgCity = 24,
			.mpgHighway = 30,
			.fullTank = 16
		}
	};

	printCar(car);

	struct car car2 = {
		.year = "2023",
		.make = TOYOTA,
		.model = "Corolla",
		.color = writeColor(255, 250, 34),
		.doors = 4,
		.seats = 5,
		.odometer = 2000,
		.runType.electric = {
			.chargingTime = 12,
			.MPGe = 112,
			.range = 245
		}
	};

	printCar(car2);

	return 0;
}
