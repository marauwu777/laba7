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
	// �������
	void clear();
	// ����������� �������������
	TVector(int size = 0, const T* NewData = nullptr);
	// ����� �����������
	TVector(const TVector<T>& vec);
	// ����������
	virtual ~TVector();
	// ����������� ������
	void copyobj(const TVector<T>& vec);
	// ����������� ������ � ������
	int copy(const int New_size, const T* New_data);
	// �����
	void print();
	// �����������
	void add(TVector<T>& vec);
	//���������
	void subtract(TVector<T>& vec);
	//������
	double length();
	// ��������� ������������
	template <typename U>
	friend double scalar_product(TVector<U>& vec1, TVector<U>& vec2);
	// �����
	template <typename U>
	friend TVector<U> sum(TVector<U>& vec1, TVector<U>& vec2);
	// ��������
	template <typename U>
	friend TVector<U> diff(TVector<U>& vec1, TVector<U>& vec2);
	// �������� ������������
	TVector& operator=(TVector<T>& vec);
	// l-value
	T& operator[](int index);
	// r-value
	T operator[](int index) const;
	// �������� ���������� ������������
	template <typename U>
	friend double operator*(TVector<U>& vec1, TVector<U>& vec2);
	// �������� �����
	template <typename U>
	friend TVector<U> operator+(TVector<U>& vec1, TVector<U>& vec2);
	// �������� ��������
	template <typename U>
	friend TVector<U> operator-(TVector<U>& vec1, TVector<U>& vec2);
	// �������� �����������
	TVector& operator+=(TVector<T>& vec);
	// �������� ���������
	TVector& operator-=(TVector<T>& vec);
	// ������� ������
	T operator()();
	// ����������� �����������
	TVector(TVector<T>&& vec);
	// �������� �����������
	TVector& operator=(TVector<T>&& vec);
};

template <typename T>
void TVector<T>::init()
{
	size = 0;
	data = nullptr;
}

// �������
template <typename T>
void TVector<T>::clear() {
	delete[] data;
	init();
}
// ����������� ������
template <typename T>
void TVector<T>::copyobj(const TVector<T>& vec) {
	if (this == &vec) {
		return;
	}
	copy(vec.size, vec.data);
}
// ����������� ������ � ������
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
// ����������� �������������
template <typename T>
TVector<T>::TVector(const int NewSize, const T* NewData) {
	init();
	copy(NewSize, NewData);

}
// ����� �����������
template <typename T>
TVector<T>::TVector(const TVector<T>& vec) {
	cout << " copy constructor" << endl;
	init();
	copyobj(vec);
}
// ����������
template <typename T>
TVector<T>::~TVector() {
	clear();
}
// �����
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
// ��������� ������������
template <typename T>
double scalar_product(TVector<T>& vec1, TVector<T>& vec2) {
	double result = 0;
	int s = min(vec1.size, vec2.size);
	for (int i = 0; i < s; i++) {
		result += vec1.data[i] * vec2.data[i];
	}
	return result;

}

// ������
template <typename T>
double TVector<T>::length() {
	return(sqrt(scalar_product(*this, *this)));
}
// �����
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
// ��������
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

// �����������
template <typename T>
void TVector<T>::add(TVector<T>& vec) {
	this->copyobj(sum(*this, vec));
}
// ���������
template <typename T>
void TVector<T>::subtract(TVector& vec) {
	this->copyobj(diff(*this, vec));
}
// �������� ������������
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
// �������� ���������� ������������
template <typename T>
double operator*(TVector<T>& vec1, TVector<T>& vec2) {
	return scalar_product(vec1, vec2);
}
// �������� �����
template <typename T>
TVector<T> operator+(TVector<T>& vec1, TVector<T>& vec2) {
	return sum(vec1, vec2);
}
// �������� ��������
template <typename T>
TVector<T> operator-(TVector<T>& vec1, TVector<T>& vec2) {
	return diff(vec1, vec2);
}
// �������� �����������
template <typename T>
TVector<T>& TVector<T>::operator+=(TVector<T>& vec) {
	this->add(vec);
	return *this;
}
// �������� ���������
template <typename T>
TVector<T>& TVector<T>::operator-=(TVector<T>& vec) {
	this->subtract(vec);
	return *this;
}
// ������� ������
template <typename T>
T TVector<T>::operator()() {
	return this->length();
}
// ������� ����� vprint
template <typename T>
void TVector<T>::vprint() {
	print();
}
// ���� ������������ �����������
template <typename T>
TVector<T>::TVector(TVector<T>&& vec) : size(vec.size), data(vec.data) {
	cout << "Move constructor" << endl;
	vec.init();
}
// �������� �����������
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
