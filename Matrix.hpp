#pragma once 
#include <vector>
template<typename T> class Matrix{
	
	public:
		int m_length; 
		int m_width; 
		std::vector<std::vector<T> > m_matrix;

	Matrix(int length, int width):m_length(length), m_width(width), m_matrix(width, std::vector<T>(length, 0)){};
	
	void set_entry(int i, int j, T value){
		m_matrix[i][j] = value;
	}	

	T get_entry(int i, int j){
		return m_matrix[i][j];
	}
};