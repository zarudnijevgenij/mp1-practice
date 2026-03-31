#include <iostream>
#include <cmath>

class V {
private:
	int n;
	double* x;
public:
	V(int n);
	V(const V& v);
	~V();
	int size() const;
	double len() const;
	V operator +(const V& v);
	double operator *(const V& v);
	bool operator ==(const V& v);
	const V operator =(const V& v);
	friend std::ostream& operator <<(std::ostream& out, const V& v) {
		for (int i = 0; i < v.n; i++) {
			out << v.x[i] << " ";
		}
		out << "\n";
		return out;
	}
	friend std::istream& operator >>(std::istream& in, V& v) {
		for (int i = 0; i < v.n; i++) {
			in >> v.x[i];
		}
		return in;
	}
};
V::V(int n) {
	this->n = n;
	x = new double[n];
}
V::V(const V& v) {
	this->n = v.n;
	x = new double[n];
	for (int i = 0; i < n; i++) {
		x[i] = v.x[i];
	}
}
V::~V() {
	delete[]x;
}
int V::size() const {
	return n;
}
double V::len() const {
	double s = 0;
	for (int i = 0; i < n; i++) {
		s += x[i] * x[i];
	}
	return sqrt(s);
}
V V::operator +(const V& v) {
	if (n != v.n) {
		throw "error";
	}
	V result(n);
	for (int i = 0; i < n; i++) {
		result.x[i] = x[i] + v.x[i];
	}
	return result;
}
double V::operator *(const V& v) {
	if (n != v.n) {
		throw "error";
	}
	double s = 0;
	for (int i = 0; i < n; i++) {
		s += x[i] * v.x[i];
	}
	return s;
}
bool V::operator ==(const V& v) {
	if (n != v.n) return 0;
	for (int i = 0; i < n; i++) {
		if (x[i] != v.x[i]) return 0;
	}
	return 1;
}
const V V::operator =(const V& v) {
	V result(n);
	for (int i = 0; i < n; i++) {
		result.x[i] = v.x[i];
	}
	return result;
}


int main() {
	V a(2), b(2);
	std::cin >> a;
	std::cin >> b;
	double c = a * b;
	printf("%f", c);

}