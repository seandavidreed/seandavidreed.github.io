/*
 * fraction.c
 *
 *  Created on: Feb 13, 2023
 *      Author: seandavidreed
 *
 *  Sources:
 *  Compute the integer absolute value (abs) without branching
 *  https://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
 */


#include <stdio.h>
#include <stdint.h>

typedef struct {
	int32_t numer;
	int32_t denom;
} fraction;

uint32_t absolute(int32_t num) {
	const int32_t mask = num >> ((sizeof(num) * 8) - 1);
	return (num ^ mask) - mask;
}

void reduce(fraction *reduce) {

	uint32_t test = absolute(reduce->numer);
	uint32_t test2 = absolute(reduce->denom);

	uint32_t smaller = (test < test2) ? test : test2;
	smaller /= 2;

	for (int i = 2; i <= smaller; ++i) {
		while ((reduce->numer % i == 0) && (reduce->denom % i == 0)) {
			reduce->numer /= i;
			reduce->denom /= i;
		}
	}
}

fraction add(fraction* addend1, fraction* addend2) {
	fraction sum;
	sum.numer = (addend1->numer * addend2->denom)
			+ (addend2->numer * addend1->denom);
	sum.denom = addend1->denom * addend2->denom;

	reduce(&sum);

	return sum;
}

fraction subtract(fraction *minuend, fraction *subtrahend) {
	fraction difference;
	difference.numer = (minuend->numer * subtrahend->denom)
			- (subtrahend->numer * minuend->denom);
	difference.denom = minuend->denom * subtrahend->denom;

	reduce(&difference);

	return difference;
}

fraction multiply(fraction *factor1, fraction *factor2) {
	fraction product = {
		.numer = factor1->numer * factor2->numer,
		.denom = factor1->denom * factor2->denom
	};

	reduce(&product);

	return product;
}

fraction divide(fraction *dividend, fraction *divisor) {
	fraction quotient = {
		.numer = dividend->numer * divisor->denom,
		.denom = dividend->denom * divisor->numer
	};

	reduce(&quotient);

	return quotient;
}

void printFrac(fraction *fraction) {
	if (fraction->numer == fraction->denom) {
		puts("1");
	} else {
		printf("%d/%d\n", fraction->numer, fraction->denom);
	}
}

int main() {

	fraction test = {1234, 80};
	fraction test2 = {231, 3};

	fraction result = add(&test, &test2);
	printFrac(&result);

	result = subtract(&test, &test2);
	printFrac(&result);

	result = multiply(&test, &test2);
	printFrac(&result);

	result = divide(&test, &test2);
	printFrac(&result);

	return 0;
}
