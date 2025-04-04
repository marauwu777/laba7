#pragma once
#include <iostream>
using namespace std;

template <typename T>
class TVector{
protected:
	int size;
	T* data;
private:
	void init();
public:
	virtual void vprint();
	// очистка
	void clear();
	// Конструктор инициализации
	TVector(int size = 0, const T* NewData = nullptr);
	// Копия конструктор
	TVector(const TVector<T>& vec);
	// Деструктор
	virtual ~TVector();
	// Копирование объект
	void copyobj(const TVector<T>& vec);
	// Копирование размер и данные
	int copy(const int New_size, const T* New_data);
	// Вывод
	void print();
	// прибавление
	void add(TVector<T>& vec);
	//вычитание
	void subtract(TVector<T>& vec);
	//модуль
	double length();
	// скалярное произведение
	template <typename U>
	friend double scalar_product(TVector<U>& vec1, TVector<U>& vec2);
	// сумма
	template <typename U>
	friend TVector<U> sum(TVector<U>& vec1, TVector<U>& vec2);
	// разность
	template <typename U>
	friend TVector<U> diff(TVector<U>& vec1, TVector<U>& vec2);
	// оператор присваивания
	TVector& operator=(TVector<T>& vec);
	// l-value
	T& operator[](int index);
	// r-value
	T operator[](int index) const;
	// оператор скалярного произведения
	template <typename U>
	friend double operator*(TVector<U>& vec1, TVector<U>& vec2);
	// опреатор суммы
	template <typename U>
	friend TVector<U> operator+(TVector<U>& vec1, TVector<U>& vec2);
	// оператор разности
	template <typename U>
	friend TVector<U> operator-(TVector<U>& vec1, TVector<U>& vec2);
	// оператор прибавления
	TVector& operator+=(TVector<T>& vec);
	// оператор вычитания
	TVector& operator-=(TVector<T>& vec);
	// функтор модуль
	T operator()();
	// конструктор перемещения
	TVector(TVector<T>&& vec);
	// оператор перемещения
	TVector& operator=(TVector<T>&& vec);
};

template <typename T>
void TVector<T>::init()
{
	size = 0;
	data = nullptr;
}

// очистка
template <typename T>
void TVector<T>::clear() {
	delete[] data;
	init();
}
// Копирование объект
template <typename T>
void TVector<T>::copyobj(const TVector<T>& vec) {
	if (this == &vec) {
		return;
	}
	copy(vec.size, vec.data);
}
// копирование размер и данные
template <typename T>
int TVector<T>::copy(const int New_size, const T* New_data) {
	if (data != New_data) {
		clear();
		data = new T[New_size];
		if (data) {
			size = New_size;
			for (int i = 0; i < size; i++) {
				data[i] = New_data[i];
			}
		}
	}
	return New_size;
}
// Конструктор инициализации
template <typename T>
TVector<T>::TVector(const int NewSize, const T* NewData) {
	init();
	copy(NewSize, NewData);

}
// Копия конструктор
template <typename T>
TVector<T>::TVector(const TVector<T>& vec) {
	cout << " copy constructor" << endl;
	init();
	copyobj(vec);
}
// Деструктор
template <typename T>
TVector<T>::~TVector() {
	clear();
}
// Вывод
template <typename T>
void TVector<T>::print() {
	cout << "Num: " << size << " Data: ";
	if (data) {
		for (int i = 0; i < size; i++) {
			cout << data[i] << " ";
		}
	}
	else {
		cout << "NULL";
	}
	cout << endl;
}
// скалярное произведение
template <typename T>
double scalar_product(TVector<T>& vec1, TVector<T>& vec2) {
	double result = 0;
	int s = min(vec1.size, vec2.size);
	for (int i = 0; i < s; i++) {
		result += vec1.data[i] * vec2.data[i];
	}
	return result;

}

// модуль
template <typename T>
double TVector<T>::length() {
	return(sqrt(scalar_product(*this, *this)));
}
// сумма
template <typename T>
TVector<T> sum(TVector<T>& vec1, TVector<T>& vec2) {
	int smin = min(vec1.size, vec2.size);
	int smax = max(vec1.size, vec2.size);
	T* resultData = new T[smax];

	for (int i = 0; i < smin; i++) {
		resultData[i] = vec1.data[i] + vec2.data[i];
	}
	for (int i = smin; i < vec1.size; i++) {
		resultData[i] = vec1.data[i];
	}
	for (int i = smin; i < vec2.size; i++) {
		resultData[i] = vec2.data[i];
	}
	TVector<T> result;
	result.size = smax;
	result.data = resultData;
	return result;
}
// разность
template <typename T>
TVector<T> diff(TVector<T>& vec1, TVector<T>& vec2) {
	int smin = min(vec1.size, vec2.size);
	int smax = max(vec1.size, vec2.size);
	T* resultData = new T[smax];

	for (int i = 0; i < smin; i++) {
		resultData[i] = (vec1.data[i] - vec2.data[i]);
	}
	for (int i = smin; i < vec1.size; i++) {
		resultData[i] = vec1.data[i];
	}
	for (int i = smin; i < vec2.size; i++) {
		resultData[i] = -vec2.data[i];
	}
	TVector<T> result;
	result.size = smax;
	result.data = resultData;
	return result;
}

// прибавление
template <typename T>
void TVector<T>::add(TVector<T>& vec) {
	this->copyobj(sum(*this, vec));
}
// вычитание
template <typename T>
void TVector<T>::subtract(TVector& vec) {
	this->copyobj(diff(*this, vec));
}
// оператор присваивания
template <typename T>
TVector<T>& TVector<T>::operator=(TVector<T>& vec) {
	cout << "=copy" << endl;
	if (this != &vec) {
		copyobj(vec);
	}
	return *this;
}
// l-value
template <typename T>
T& TVector<T>::operator[](int index) {
	return data[index];
}
// r-value
template <typename T>
T TVector<T>::operator[](int index) const {
	return data[index];
}
// оператор скалярного произведения
template <typename T>
double operator*(TVector<T>& vec1, TVector<T>& vec2) {
	return scalar_product(vec1, vec2);
}
// оператор суммы
template <typename T>
TVector<T> operator+(TVector<T>& vec1, TVector<T>& vec2) {
	return sum(vec1, vec2);
}
// опреатор разности
template <typename T>
TVector<T> operator-(TVector<T>& vec1, TVector<T>& vec2) {
	return diff(vec1, vec2);
}
// оператор прибавления
template <typename T>
TVector<T>& TVector<T>::operator+=(TVector<T>& vec) {
	this->add(vec);
	return *this;
}
// оператор вычитания
template <typename T>
TVector<T>& TVector<T>::operator-=(TVector<T>& vec) {
	this->subtract(vec);
	return *this;
}
// функтор модуль
template <typename T>
T TVector<T>::operator()() {
	return this->length();
}
// Базовый класс vprint
template <typename T>
void TVector<T>::vprint() {
	print();
}
// копи перемещением конструктор
template <typename T>
TVector<T>::TVector(TVector<T>&& vec) : size(vec.size), data(vec.data) {
	cout << "Move constructor" << endl;
	vec.init();
}
// оператор перемещение
template <typename T>
TVector<T>& TVector<T>::operator=(TVector<T>&& vec) {
	cout << "=Move" << endl;
	if (this != &vec) {
		clear();
		size = vec.size;
		data = vec.data;
		vec.init();
	}
	return *this;
}
