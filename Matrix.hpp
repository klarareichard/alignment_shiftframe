#pragma once 
#include <vector>
#include <iostream>
template<typename T> class Matrix{
	
	public:
		int m_length; 
		int m_width; 
		std::vector<std::vector<T> > m_matrix;

		
	Matrix(int length, int width):m_length(length), m_width(width), m_matrix(length, std::vector<T>(width, 0)){};
	
	void set_entry(int i, int j, T value){
		m_matrix[i][j] = value;
	}	

	T get_entry(int i, int j){
		if((i == -1) || (j == -1)){
			return 0;
		}else{
			return m_matrix[i][j];
		}
	}

	int get_length(){
		return m_length;
	}

	int get_width(){
		return m_width;
	}

	void print(std::string name){
		for(int i = 0; i < this->get_length(); ++i){
			for(int j = 0; j < this->get_width(); ++j){
				std::cout<< name<<"[ "<<i<<" ][ "<<j<<"] = "<< this->get_entry(i,j)<<std::endl;
			}
		}
	}
};