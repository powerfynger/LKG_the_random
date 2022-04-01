#include <stdio.h>
#include "string.h"
#include <stdlib.h>

#define FILENAME_OUT		"output.txt"
#define FILENAME_IN			"input.txt"

void get_c(unsigned long long* list);
unsigned long long get_a();
void lcg(unsigned long long a, unsigned long long x, unsigned long long c, unsigned long long m, unsigned long long n);
void lcg_init();
void bits_lcg(unsigned long long a, unsigned long long x, unsigned long long c, unsigned long long m, unsigned long long n, unsigned long long* mass);
void read_command(char* command);
void bits_init();
unsigned long long read_num_ulonglong(FILE* file);
unsigned long long bin_pow_ulonglong(unsigned short s);
unsigned short read_num_ushort(FILE* file);
unsigned long long is_coprime(unsigned long long c, unsigned long long m);
char is_prime(unsigned long long n);

unsigned long long max_n = 0;

int main() {
	FILE* file_output;
	if (!fopen_s(&file_output, FILENAME_OUT, "w")) {
		fclose(file_output);
	}
	else {
		printf("Error while creating output file.\n");
	}
	char command[8] = { '\0' };
	read_command(command);
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
		unsigned long long a = 0;
		a = get_a();
		FILE* file_output;
		if (fopen_s(&file_output, FILENAME_OUT, "w")) {
			printf("Unable to create output file.\n");
			exit(-1);
		}
		if (a == 2) {
			fprintf_s(file_output, "no solution");
		}
		else {
			fprintf_s(file_output, "%llu\n", a);
		}

	}
	else if (!strcmp(command, "lcg")) {
		lcg_init();
	}
	else if (!strcmp(command, "bits")) {
		bits_init();
	}
	else {
		FILE* file_output;
		if (!fopen_s(&file_output, FILENAME_OUT, "w")) {
			fprintf_s(file_output, "incorrect command"); exit(0);
		}
		else {
			printf("Error while creating output file.\n");
		}
		exit(-1);
	}

	_fcloseall();
	return 0;
}

void get_c(unsigned long long* list_of_c) {
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
			fprintf_s(file_output, "incorrect command"); exit(0);
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
}

unsigned long long get_a() {
	FILE* file_input;
	// Переменная отвечает за проверку количества аргументов
	char change = 0;
	unsigned long long m = 0, a = 2, i = 1;
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
	}
	// Проверка на количество аргументов
	if (change != 1) {
			FILE* file_output;
			if (!fopen_s(&file_output, FILENAME_OUT, "w")) {
				fprintf_s(file_output, "incorrect command"); exit(0);
			}
			else {
				printf("Error while creating output file.\n");
			}
			exit(-1);
		}
	
	if (m % 4 == 0) {
		while (a < (m ^ (1 / 2)) + 1) {
			while (i < (m ^ (1 / 2) + 1)) {
				if (m % i == 0) {
					if (is_prime(i)) {
						if ((a-1) % i != 0 || (a-1) % 4 != 0 ) {
							change = 0;
							break;

						}
					}
				}
				i++;
			}
			if (change) {
				break;
			}
			change = 1;
			i = 1;
			a++;

		}
	}
	else{
		while (a < (m ^ (1 / 2)) + 1) {
			while (i < (m ^ (1 / 2) + 1)) {
				if (m % i == 0) {
					if (is_prime(i)) {
						if ((a-1) % i != 0) {
							change = 0;
							break;

						}
					}
				}
				i++;
			}
			if (change) {
				break;
			}
			change = 1;
			i = 1;
			a++;

		}
	}
	return a;
}

void lcg(unsigned long long a, unsigned long long x, unsigned long long c, unsigned long long m, unsigned long long n) {
	if (n > max_n) {
		return;
	}
	lcg(a, (a*x+c) % m, c, m, n + 1);
	FILE* file_output;
	if (fopen_s(&file_output, FILENAME_OUT, "a+")) {
		printf("Unable to create output file.\n");
		exit(-1);
	}
	fprintf_s(file_output, "%llu\n", x);
	fclose(file_output);
}

void bits_lcg(unsigned long long a, unsigned long long x, unsigned long long c, unsigned long long m, unsigned long long n, unsigned long long* mass) {
	if (n > max_n) {
		return;
	}
	bits_lcg(a, (a * x + c) % m, c, m, n + 1, mass);
	int i = 0;
	while (x != 0 || i != 63) {
		mass[i] += x % 2;
		x = x / 10;
		i++;
	}
}

void bits_init() {
	FILE* file_input;
	// Переменная отвечает за проверку количества аргументов
	char change = 0;
	unsigned long long m = 0, c = 0, x0 = 0, a = 0; // 0 <= a, x0, c, m, n <= 2^64 - 1; a, x0, c < m; !(n = 0 || a, c, x0 >= m)
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
		case 'c':
			curr_char = fgetc(file_input);
			if (curr_char == 'g') {
				break;
			}
			c = read_num_ulonglong(file_input);
			change++;
			break;
		case 'x':
			curr_char = fgetc(file_input);
			curr_char = fgetc(file_input);
			x0 = read_num_ulonglong(file_input);
			change++;
			break;
		case 'a':
			curr_char = fgetc(file_input);
			a = read_num_ulonglong(file_input);
			change++;
			break;
		case 'n':
			curr_char = fgetc(file_input);
			max_n = read_num_ulonglong(file_input);
			change++;
			break;
		default:
			break;
		}
	}
	// Проверка на количество аргументов
	if (change != 5) {
		FILE* file_output;
		if (!fopen_s(&file_output, FILENAME_OUT, "w")) {
			fprintf_s(file_output, "incorrect command"); exit(0);
		}
		else {
			printf("Error while creating output file.\n");
		}
		exit(-1);
	}
	if (max_n == 0 || a >= m || c >= m || x0 >= m || a < 0) {
		FILE* file_output;
		if (!fopen_s(&file_output, FILENAME_OUT, "w")) {
			fprintf_s(file_output, "no solution"); exit(0);
		}
		else {
			printf("Error while creating output file.\n");
		}
		exit(-1);
	}
	unsigned long long mass[64] = { 0 };
	bits_lcg(a, x0, c, m, 1, mass);
	FILE* file_output;
	if (fopen_s(&file_output, FILENAME_OUT, "a+")) {
		printf("Unable to create output file.\n");
		exit(-1);
	}
	for (int i = 0; i < 63; i++) {
		fprintf_s(file_output, "%llu\n", mass[i]);
	}
	fclose(file_output);
}

void lcg_init() {
	FILE* file_input;
	// Переменная отвечает за проверку количества аргументов
	char change = 0;
	unsigned long long m = 0, c = 0, x0 = 0, a = 0; // 0 <= a, x0, c, m, n <= 2^64 - 1; a, x0, c < m; !(n = 0 || a, c, x0 >= m)
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
		case 'c':
			curr_char = fgetc(file_input);
			if (curr_char == 'g') {
				break;
			}
			c = read_num_ulonglong(file_input);
			change++;
			break;
		case 'x':
			curr_char = fgetc(file_input);
			curr_char = fgetc(file_input);
			x0 = read_num_ulonglong(file_input);
			change++;
			break;
		case 'a':
			curr_char = fgetc(file_input);
			a = read_num_ulonglong(file_input);
			change++;
			break;
		case 'n':
			curr_char = fgetc(file_input);
			max_n = read_num_ulonglong(file_input);
			change++;
			break;
		default:
			break;
		}
	}
	// Проверка на количество аргументов
	if (change != 5) {
		FILE* file_output;
		if (!fopen_s(&file_output, FILENAME_OUT, "w")) {
			fprintf_s(file_output, "incorrect command"); exit(0);
		}
		else {
			printf("Error while creating output file.\n");
		}
		exit(-1);
	}
	if (max_n == 0 || a >= m || c >= m || x0 >= m || a < 0) {
		FILE* file_output;
		if (!fopen_s(&file_output, FILENAME_OUT, "w")) {
			fprintf_s(file_output, "no solution"); exit(0); 
		}
		else {
			printf("Error while creating output file.\n");
		}
		exit(-1);
	}
	lcg(a, x0, c, m, 1);
}

void read_command(char* command) {
	FILE* file_input;
	if (fopen_s(&file_input, FILENAME_IN, "r")) {
		printf("Input file was not found.\n");
		exit(-1);
	}
	char c = '\0';
	for (int i = 0; i < 6; i++) {
		c = fgetc(file_input);
		if (c == ' ') {
			break;
		}
		command[i] = c;
	}
	fclose(file_input);
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
				fprintf_s(file_output, "incorrect command"); exit(0);
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
				fprintf_s(file_output, "incorrect command"); exit(0);
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

char is_prime(unsigned long long n){
	if (n >= 1){
		for (unsigned long long i = 2; i < n; i++)
			if (n % i == 0)
				return 0;
		return 1;
	}
	else
		return 0;
}