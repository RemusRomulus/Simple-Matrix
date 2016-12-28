#include <iomanip>
#include <vector>
#include <cmath>
#include <iostream>

//  0  1  2  3
//  4  5  6  7
//  8  9 10 11
// 12 13 14 15
// This Deals with strictly square matrices


template <typename T>
class Matrix
{
public:
	Matrix() { data = { 0 }; }
	Matrix(std::vector<T> &rhs) : data(rhs)
	{
		data = rhs;
		if (!this->size_dim())
		{
			this->clear();
			std::cout << "::ERROR:: Matrix<T> cannot initialize with non-square matrix\n";
		}
	}
	Matrix(T in)
	{
		this->data.push_back(in);
		this->size_dim();
	}
	~Matrix() { data.clear(); }
	Matrix & operator=(const Matrix &rhs)
	{
		this->data = rhs.data;
		this->dim = rhs.dim;
	}


	void print()
	{
		std::cout << "-----\nMatrix Data\n-----\n";
		std::cout << "-- Matrix Dim: " << this->dim << "\n-----\n";

		long long counter = 1;
		for (auto &&e : this->data)
		{
			std::cout <<std::setprecision(6) << e << ", ";
			if (counter % dim == 0)
				std::cout << "\n";
			counter++;
		}
		std::cout << "-----\n\n";
	}

	void print_corners()
	{
		std::cout << "-----\nMatrix Data: Corners\n-----\n";
		std::cout << "-- Matrix Dim: " << this->dim << "\n-----\n";

		std::cout << std::setprecision(6) << this->data[0] << " -- " << this->data[dim - 1] << "\n";
		std::cout << "|    |\n";
		std::cout << std::setprecision(6) << this->data[dim * dim - dim] << " -- " << this->data[dim*dim - 1] << "\n\n";
	}

	void transpose()
	{
		unsigned int size_mtx = unsigned int(this->data.size());

		if (size_mtx > 1)
		{
			std::vector<T> tmp_vect(dim, 0);

			for (unsigned int i = 0; i < size_mtx - dim - 1; i += dim + 1)
			{
				for (unsigned int j = 0; j < dim; j++)
				{
					//Keeps the array index in bounds
					if (i + dim * j > size_mtx)
						continue;

					//std::cout << "i: " << i << ", j: " << j << ", i + j: " << i+j << ", i + dim * j: " << i + dim*j << "\n";
					tmp_vect[j] = this->data[i + dim * j];

					this->data[i + dim * j] = this->data[i + j];
					this->data[i + j] = tmp_vect[j];
				}
			}
		}
	}

	inline void clear()
	{
		this->data.clear();
		dim = 0;
	}

private:
	inline bool size_dim()
	{
		bool OUT = false;
		this->dim = unsigned int(std::sqrt(this->data.size()));
		if (dim * dim == data.size())
			OUT = true;
		
		// no else statement since OUT is initialized as false
		return OUT;
	}

	std::vector<T> data;
	unsigned int dim;
};


template<>
class Matrix<char>
{
public:
	Matrix(...)
	{
		std::cout << "::ERROR:: Matrix can't initialize with type <CHAR>.\n";
	}

	void print()
	{
		std::cout << "-----\nMatrix Data\n-----\n";
		std::cout << "-- Matrix Dim: " << 0 << "\n-----\n";
		std::cout << "-----\n\n";
	}

	void print_corners()
	{
		std::cout << "-----\nMatrix Data: Corners\n-----\n";
		std::cout << "-- Matrix Dim: " << 0 << "\n-----\n";
		std::cout << "-----\n\n";
	}

private:
	// data and dim attributes are not included, to ensure that an improperly created class
	// will not accidentally be put to use in production code later
};


template <>
class Matrix<std::string>
{
public:
	Matrix(...)
	{
		std::cout << "::ERROR:: Matrix can't initialize with type <STD::STRING>.\n";
	}

	void print()
	{
		std::cout << "-----\nMatrix Data\n-----\n";
		std::cout << "-- Matrix Dim: " << 0 << "\n-----\n";
		std::cout << "-----\n\n";
	}

	void print_corners()
	{
		std::cout << "-----\nMatrix Data: Corners\n-----\n";
		std::cout << "-- Matrix Dim: " << 0 << "\n-----\n";
		std::cout << "-----\n\n";
	}

private:
	// data and dim attributes are not included, to ensure that an improperly created class
	// will not accidentally be put to use in production code later
};



int main()
{
	//Check floats
	std::cout << "\n............\n Check FLOATs\n";
	std::vector<float> mtx_array = { 1.0f, 2.0f, 3.3f, 4.4f, 5.5f, \
								   	6.6f, 7.7f, 8.8f, 9.9f, 10.1f, \
								   	11.4f, 12.2f, 13.3f, 14.4f, 15.5f, \
								   	16.6f };
	Matrix<float> mtx(mtx_array);
	mtx.print();
	mtx.print_corners();
	mtx.transpose();
	mtx.print();
	mtx.print_corners();


	//Check single double
	std::cout << "\n............\n Check Single DOUBLE\n";
	Matrix<double> mtx_single_double(34.0004);
	mtx_single_double.print();
	mtx_single_double.transpose();
	mtx_single_double.print();


	//Check Non Square list
	std::cout << "\n............\n Check NON Square MTX\n";
	std::vector<double> mtx_double_array = {97.346335, 872.982734, 98.2398235, -.0293982, -29083.2352};
	Matrix<double> mtx_double(mtx_double_array);
	mtx_double.print();
	mtx_double.transpose();
	mtx_double.print();


	//Check Single item
	std::cout << "\n............\n Check Single Item\n";
	Matrix<int> mtx_single(235);
	mtx_single.print();
	mtx_single.transpose();
	mtx_single.print();


	//Testing Copy Operator
	std::cout << "\n............\n Check Copy Operator\n";
	Matrix<float> mtx_float_2 = mtx;
	mtx_float_2.print();


	//Check Ints
	std::cout << "\n............\n Check INTs\n";
	std::vector<int> int_mtx_array = { 1, 2, 3, 4, 5, 6, \
										7, 8, 9, 10, 11, 12, \
										13, 14, 15, 16, 17, 18, \
										19, 20, 21, 22, 23, 24, \
										25, 26, 27, 28, 29, 30, \
										31, 32, 33, 34, 35, 36 };
	Matrix<int> mtx_int(int_mtx_array);
	mtx_int.print();
	mtx_int.transpose();
	mtx_int.print();


	//Check Large Squares of LONG LONG
	std::cout << "\n............\n Check LONG LONGs\n";
	std::vector<long long> double_long_array(1000 * 1000, 0);
	long long count = 0;
	for (auto &&e : double_long_array)
		e = count++;
	Matrix<long long> mtx_long_long(double_long_array);
	mtx_long_long.print_corners();
	mtx_long_long.transpose();
	mtx_long_long.print_corners();


	// Ensuring that trying to instantiate a Matrix<char> will fail with defined message
	Matrix<char> mtx_char;
	Matrix<char> mtx_char_2('g');
	Matrix<std::string> mtx_str;
	Matrix<std::string> mtx_str_2("foo");



	// Just using this to keep the output window open long enough to visually check the results
	char tmp;
	std::cin >> tmp;

	return 0;
}