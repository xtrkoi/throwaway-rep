// DataGenerator.h
#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

const int num_data_sizes = 9;
extern const int data_sizes[num_data_sizes];

const int num_data_props = 5;
extern const char * data_props[num_data_props];

void GenerateData(int a[], int n, int dataType);

#endif