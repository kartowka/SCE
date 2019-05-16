//LAB-11 SCE-Campus Ashdod//
//RECURSIVE//
//Author: Anthony Eitan Fleysher//
//ID: 203192331// 


#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

////EXERCISE1//
//int f1(int);
//int main() {
//	int num;
//	puts("enter number");
//	scanf("%d", &num);
//	printf("%d",f1(num));
//	return 0;
//}
//
//int f1(int num) {
//	if (num < 10)
//		return 1;
//	return 1 + f1(num / 10);
//
//}

////EXERCISE2//
//
//int f2v1(int);
//int f2v2(int,int);
//
//int main() {
//	int num,num1;
//	puts("enter start number");
//	scanf("%d", &num);
//	puts("enter end number");
//	scanf("%d", &num1);
//	f2v1(num);
//	printf("\n");
//	f2v2(num,num1);
//	return 0;
//}
//
//int f2v1(int num) {
//	printf("%d", num);
//	if (num==1)
//		return 0;
//	return num - f2v1(num - 1);
//}
//int f2v2(int num,int num1) {
//	printf("%d", num);
//	if (num == num1)
//		return 0;
//	return f2v2(num + 1, num1);
//}

////EXERCISE3//

//int printBinary(int);
//
//int main() {
//	int num;
//	puts("enter number");
//	scanf("%d", &num);
//	printf("%d",printBinary(num));
//	return 0;
//}
//
//int printBinary(int num) {
//	if (num == 0)
//		return 0;
//	if (num == 1)
//		return 1;
//	return num % 2 + 10 * printBinary(num / 2);
//}

//EXERCISE4//

//int f4(int, int);
//
//int main() {
//	int num1, num2;
//	puts("enter first number");
//	scanf("%d", &num1);
//	puts("enter second number");
//	scanf("%d", &num2);
//	printf("%d",f4(num1, num2));
//	return 0;
//}
//
//int f4(int num1, int num2) {
//	if (num2 == 0)
//		return 0;
//	if (num2 > 0)
//		return num1 + f4(num1, num2 - 1);
//	else
//		return -num1 + f4(num1, num2 + 1);
//}

////EXERCISE5//

//int f5(int, int);
//
//int main() {
//	int num1, num2;
//	puts("enter first number");
//	scanf("%d", &num1);
//	puts("enter second number");
//	scanf("%d", &num2);
//	printf("%d",f5(num1, num2));
//}
//
//int f5(int num1, int num2) {
//	if (num2 != 0)
//		return f5(num2, num1%num2);
//	return num1;
//}

////EXERCISE6//

//int f6(int*, int);
//
//int main() {
//	int arr[6] = { 3, 5, 2, 1, 8,1 };
//	int size = sizeof(arr) / sizeof(int);
//	f6(arr, size);
//}
//
//int f6(int* arr, int size) {
//	printf("%d ", *arr);
//	if (size==1)
//		return 0;
//	return f6(arr + 1, size - 1);
//}

////EXERCISE7//

//void f7(int*, int);
//
//int main() {
//	int arr[6] = { 3, 5, 2, 1, 8,1 };
//	int size = sizeof(arr) / sizeof(int);
//	f7(arr, size);
//}
//
//void f7(int* arr, int size) {
//	if (size > 0) {
//		size--;
//		printf("%d", arr[size]);
//		f7(arr, size);
//	}
//}

////EXERCISE8//

//int f8(int*, int);
//
//int main() {
//	int arr[6] = { 3, 5, 2, 1, 8,1 };
//	int size = sizeof(arr) / sizeof(int);
//	printf("%d",f8(arr, size));
//}
//
//int f8(int* arr, int size) {
//	static int max = 0;
//	if(size>0){
//		size--;
//		if (arr[size] > max)
//			max = arr[size];
//		f8(arr, size);
//
//	}
//	return max;
//}

////EXERCISE9//

//void f9(char*);
//
//int main() {
//	char str[] = "abcd";
//	f9(str);
//
//}
//
//void f9(char* str) {
//	if (*str) {
//		f9(str+1);
//		printf("%c", *str);
//	}
//}

////EXERCISE10//

//char* f10(char*,char*);
//
//int main() {
//	char str1[] = "xyz";
//	char str2[40];
//	f10(str1,str2);
//	puts(str2);
//
//}
//
//char* f10(char* str1,char* str2) {
//	if (*str1) {
//		*str2 = *str1;
//		return f10(str1 + 1, str2 + 1);
//	}
//	if (*str1 == '\0')
//		*str2 = *str1;
//	return 0;
//}

////EXERCISE11//

//void f11(char*);
//
//int main() {
//	char str[] = "xAssR";
//	f11(str);
//	return 0;
//}
//
//void f11(char* str) {
//	if (*str) {
//		if (*str >= 'a'&&*str <= 'z')
//			*str = *str + 'A' - 'a';
//		printf("%c", *str);
//		f11(str + 1);
//	}
//
//}

//EXERCISE12//

//int f12(char*);
//int f12v2(char*);
//
//int main() {
//	char str[] = "x  y z";
//	printf("%d\n",f12(str));
//	printf("%d\n", f12v2(str));
//}
//
//int f12v2(char* str) {
//	static int count = 0;
//	if (*str) {
//		if (*str == ' ')
//			count++;
//		f12v2(str + 1);
//	}
//	return count;
//}
//int f12(char* str) {
//	if (*str=='\0')
//		return 0;
//	if (*str == ' ')
//		return 1 + f12(str + 1);
//	f12(str + 1);
}