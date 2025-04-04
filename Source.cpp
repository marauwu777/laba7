#include "CVector.h"

int main() {
	int size1;
	int size2;
	while (true) {
		cout << "Enter vec1 size - ";
		cin >> size1;
		if (size1 == 0) {
			break;
		}
		cout << "Fill vec1" << endl;
		double* arr1 = new double[size1];
		for (int i = 0; i < size1; i++) {
			cout << "Vec1 element [" << i << "] - ";
			cin >> arr1[i];
			cout << endl;
		}
		cout << "Enter vec2 size - ";
		cin >> size2;
		if (size2 == 0) {
			break;
		}
		cout << "Fill vec2" << endl;
		double* arr2 = new double[size2];
		for (int i = 0; i < size2; i++) {
			cout << "Vec1 element [" << i << "] - ";
			cin >> arr2[i];
			cout << endl;
		}
		TVector<double> vec1(size1, arr1);
		TVector<double> vec2(size2, arr2);
		cout << "copy check vec3 = vec1" << endl;
		TVector<double> vec3 = vec1;
		vec3.print();
		cout << "vec1 + vec2 = " << endl;
		vec3 = vec1 + vec2;
		vec3.print();
		cout << "vec1 - vec2" << endl;
		vec3 = vec1 - vec2;
		vec3.print();
		cout << "vec1 += vec2" << endl;
		vec1 += vec2;
		vec1.print();
		cout << "vec1 -= vec2" << endl;
		vec1 -= vec2;
		vec1.print();
		cout << "vec1 * vec2" << endl;
		double result = vec1 * vec2;
		cout << "dot product = " << result << endl;
		cout << "length vec1 = " << vec1();
		delete[] arr1;
		delete[] arr2;
	}
	return 0;
}
