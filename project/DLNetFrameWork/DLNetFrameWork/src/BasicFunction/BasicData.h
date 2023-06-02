#ifndef _BASICDATA_H_
#define _BASICDATA_H_


#include<iostream>


namespace bd {
	int power(unsigned int n) {
		int result = 10;
		if (n == 0) return 1;
		else if (n == 1) return result;
		else if(n>1){
			unsigned int k = 1;
			while (k < n) {
				result = result*10;
				k++;
			}
			return result;
		}
	}


	char* intToChar(int i) {		//注意传入的参数不能超过int的范围
		//将整型数转换为字符串
		int j = i;
		unsigned int n = 0;
		while (j != 0) {
			j = i;
			n++;
			j = j / power(n);
		}
		char* array = (char*)_malloca(n+1);
		j = 0;
		while (j <n) {
			array[n - 1 - j] = (char)(i % power(j + 1) / power(j)+48);
			//std::cout << (int)&array[n - 1 - j] << " ";
			j++;
		}
		array[n] = '\0';
		return array;
	}

	char*combineChar(const char*a, const char*b){
		int lena = strlen(a), lenb = strlen(b);
		//std::cout << lena << std::endl << lenb << std::endl;
		char* ptr = (char*)_malloca((lena + lenb+1) * sizeof(char));
		int i = 0, l = -1;
		while (i < lena) {
			l++;
			ptr[l] = a[i];
			//std::cout << ptr[l] << " ";
			i++;
		}
		i = 0;
		while (i < lenb) {
			l++;
			ptr[l] = b[i];
			//std::cout << ptr[l] << " ";
			i++;
		}
		l++;
		ptr[l] = '\0';
		return ptr;
	}

	void show(char* mat) {
		int i = 0;
		while (mat[i] != '\0') {
			std::cout << mat[i];
			i++;
		}
	}

	int reverseInt(int i) {
		unsigned char ch1, ch2, ch3, ch4;
		ch1 = i & 255;
		//std::cout << ((int)ch1<<24) << std::endl;
		ch2 = (i >> 8) & 255;
		//std::cout << ((int)ch2<<16) << std::endl;
		ch3 = (i >> 16) & 255;
		//std::cout << (int)ch3 << std::endl;
		ch4 = (i >> 24) & 255;
		//std::cout << (int)ch4 << std::endl;
		return ((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
	}

}


#endif
