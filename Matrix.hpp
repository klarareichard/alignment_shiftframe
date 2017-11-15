#pragma once 
#include <vector>
#include <iostream>
template<class T> class Matrix{
	
	public:
		int m_length; 
		int m_width; 
		std::vector<std::vector<T> > m_matrix;

		
	Matrix(int length, int width):m_length(length), m_width(width), m_matrix(length, std::vector<T>(width, 0)){};
	
	void set_entry(int i, int j, T value){
		m_matrix[i][j] = value;
	}	

	template<>
	int get_entry<int>(int i, int j){

		if((i == -1) && (j >= 0)){
			return -j-1;
		}else if(i == -1){
			return 0;
		}else if((j == -1) && (i >= 0)){
			return -i-1;
		}else if(j == -1){
			return 0;
		}else{
			return m_matrix[i][j];
		}
	}

	template<>
	char get_entry<char>(int i, int j){

		if((i == -1) && (j >= 0)){
			return 'D';
		}else if(i == -1){
			return 'F';
		}else if((j == -1) && (i >= 0)){
			return 'I';
		}else if(j == -1){
			return 'F';
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
		std::cout<<name<<std::endl;
		for(int i = -1; i < this->get_length(); ++i){
			for(int j = -1; j < this->get_width(); ++j){
				/*std::cout<< name<<"[ "<<i<<" ][ "<<j<<"] = "*/ std::cout<< this->get_entry(i,j)<< " ";
			}
			std::cout<<std::endl;
		}
	}
};