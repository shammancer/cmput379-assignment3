#ifndef __SIMULATION_H__
#define __SIMULATION_H__

void process();

void init(int psize, int winsize);

void put(unsigned int address, int value);

int get(unsigned int address, int value);

extern int wordsize;

#endif
