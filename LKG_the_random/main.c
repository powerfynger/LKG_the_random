#include <stdio.h>
#include "string.h"
#include <stdlib.h>

#define FILENAME_OUT		"output.txt"
#define FILENAME_IN			"input.txt"

unsigned long long* get_c(unsigned long long* list);
void get_a();
void lcg();
void bits();
unsigned long long read_num_ulonglong(FILE* file);
unsigned long long bin_pow_ulonglong(unsigned short s);
unsigned short read_num_ushort(FILE* file);
unsigned long long is_coprime(unsigned long long c, unsigned long long m);
char is_prime(unsigned long long a, unsigned long long k);

int main() {
	FILE* file_input;
	if (fopen_s(&file_input, FILENAME_IN, "r")) {
		printf("Input file was not found.\n");
		exit(-1);
	}
	char c = '\0';
	char command[8] = {'\0'};
	for (int i = 0; i < 6; i++) {
		c = fgetc(file_input);
		if (c == ' ') {
			break;
		}
		command[i] = c;
	}
	fclose(file_input);
	if (!strcmp(command, "get_c")) {
		unsigned long long list_of_c[10] = {0};
		get_c(list_of_c);
		FILE* file_output;
		if (fopen_s(&file_output, FILENAME_OUT, "w")) {
			printf("Unable to create output file.\n");
			exit(-1);
		}
		for (int i = 0; i < 10; i++) {
			if (list_of_c[i] == 0) {
				break;
			}
			fprintf_s(file_output, "%llu\n", list_of_c[i]);
		}
	}
	else if (!strcmp(command, "get_a")) {
		get_a();
	}
	else if (!strcmp(command, "lcg")) {
		lcg();
	}
	else if (!strcmp(command, "bits")) {
		bits();
	}
	else {
		FILE* file_output;
		if (!fopen_s(&file_output, FILENAME_OUT, "w")) {
			fprintf_s(file_output, "incorrect command");
		}
		else {
			printf("Error while creating output file.\n");
		}
		exit(-1);
	}


	return 0;
}

unsigned long long* get_c(unsigned long long* list_of_c) {
	FILE* file_input;
	// Переменная отвечает за проверку количества аргументов
	char change = 0;
	unsigned short s = 0;
	unsigned long long m = 0, c = 1, max_c = 1; // c <= 2^s - 1; 0 < c < m;
	char curr_char = '\0';
	if (fopen_s(&file_input, FILENAME_IN, "r")) {
		printf("Unable access to file.\n");
		exit(-1);
	}
	// Чтение аргументов
	while (curr_char != EOF) {
		curr_char = fgetc(file_input);
		switch (curr_char)
		{
		case 'm':
			curr_char = fgetc(file_input);
			m = read_num_ulonglong(file_input);
			change++;
			break;
		case 's':
			curr_char = fgetc(file_input);
			s = read_num_ushort(file_input);
			change++;
			break;
		default:
			break;
		}
	}
	// Проверка на количество аргументов
	if (change != 2) {
		FILE* file_output;
		if (!fopen_s(&file_output, FILENAME_OUT, "w")) {
			fprintf_s(file_output, "incorrect command");
		}
		else {
			printf("Error while creating output file.\n");
		}
		exit(-1);
	}
	max_c = bin_pow_ulonglong(s) - 1;
	int i = 0;
	// Если данное число чётное - нет смысла проверять чётные числа
	if (m % 2 == 0) {
		while (c <= max_c) {
			if (is_coprime(c, m) == 1) {
				list_of_c[i] = c;
				i++;
				if (i == 10) {
					break;
				}
			}
			c += 2;
		}
	}
	else {
		while (c <= max_c) {
			if (is_coprime(c, m) == 1) {
				list_of_c[i] = c;
				i++;
				if (i == 10) {
					break;
				}
			}
			c++;
		}
	}
	return list_of_c;
}

void get_a() {
	FILE* file_input;
	// Переменная отвечает за проверку количества аргументов
	char change = 0;
	unsigned long long m = 0, a = 1, i = 1;
	char curr_char = '\0';
	if (fopen_s(&file_input, FILENAME_IN, "r")) {
		printf("Unable access to file.\n");
		exit(-1);
	}
	// Чтение аргументов
	while (curr_char != EOF) {
		curr_char = fgetc(file_input);
		if (curr_char == 'm') {
			curr_char = fgetc(file_input);
			m = read_num_ulonglong(file_input);
			change++;
		}
	// Проверка на количество аргументов
	if (change != 1) {
		FILE* file_output;
		if (!fopen_s(&file_output, FILENAME_OUT, "w")) {
			fprintf_s(file_output, "incorrect command");
		}
		else {
			printf("Error while creating output file.\n");
		}
		exit(-1);
	}
	while (m > i * i && a < m) {
		if (m % i == 0){
			if (is_prime(i,2)) {
				if(a%i)
			}
	}
}

void lcg() {


}

void bits() {


}

unsigned long long read_num_ulonglong(FILE* file_input) {
	char num[21] = { '\0' };
	char c = '\0';
	unsigned long long m = 0;
	for(int i = 0; i < 21; i++){
		c = fgetc(file_input);
		if (c == ' ' || c == EOF) {
			break;
		}
		if (c < '0' || c > '9') {
			FILE* file_output;
			if (!fopen_s(&file_output, FILENAME_OUT, "w")) {
				fprintf_s(file_output, "incorrect command");
			}
			else {
				printf("Error while creating output file.\n");
			}
			exit(-1);
		}
		num[i] = c;
	}
	m = strtoull(num, NULL, 10);
	return m;
}

unsigned short read_num_ushort(FILE* file_input) {
	char num[21] = { '\0' };
	char c = '\0';
	unsigned short s = 0;
	for (int i = 0; i < 21; i++) {
		c = fgetc(file_input);
		if (c == ' ' || c == EOF) {
			break;
		}
		if (c < '0' || c > '9') {
			FILE* file_output;
			if (!fopen_s(&file_output, FILENAME_OUT, "w")) {
				fprintf_s(file_output, "incorrect command");
			}
			else {
				printf("Error while creating output file.\n");
			}
			exit(-1);
		}
		num[i] = c;
	}
	s = (short)atoi(num);
	return s;
}

unsigned long long bin_pow_ulonglong(unsigned short s) {
	unsigned long long result = 1;
	while (s) {
		result *= 2;
		s--;

	}
	return result;
}

unsigned long long is_coprime(unsigned long long c, unsigned long long m) {
	return m ? is_coprime(m, c % m) : c;
}

char is_prime(unsigned long long a, unsigned long long k) {
	if (a < k * k) {
		return 1;
	}
	if (a % k == 0) {
		return 0;
	}
	return is_prime(a, k + 1);
}