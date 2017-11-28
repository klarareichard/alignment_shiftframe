#pragma once 
#include <vector>
#include <iostream>
template<class T> class Matrix{
	
	public:
		const int m_length;
		const int m_width;
        bool gap_opening_penalty;
		T** m_matrix;
        //T** m_matrix;

		
	Matrix(int length, int width):m_length(length), m_width(width), gap_opening_penalty(false){
        m_matrix = new T*[length+1];
        for(int i = 0; i < length+1; ++i)
            m_matrix[i] = new T[width+1];
        if(std::is_same<T,int>::value){
            m_matrix[0][0] = 0;
            for(int j = 1; j <= width; ++j){
                m_matrix[0][j] = -j-1;
            }
            for(int i = 1; i <= length; ++i){
                m_matrix[i][0] = -i-1;
            }

        }else if(std::is_same<T, char>::value){
            m_matrix[0][0] = 'F';
            for(int j = 1; j <= width; ++j){
                m_matrix[0][j] = 'I';
            }

            for(int i = 1; i <= length; ++i){
                m_matrix[i][0] = 'D';
            }
        }
    };

    Matrix(int length, int width, bool gop):m_length(length), m_width(width),  gap_opening_penalty(gop){
        m_matrix = new T*[length+1];
        for(int i = 0; i < length+1; ++i)
            m_matrix[i] = new T[width+1];
        if(std::is_same<T,int>::value){
            m_matrix[0][0] = 0;
            for(int j = 1; j <= width; ++j){
                m_matrix[0][j] = -j-12;
            }

            for(int i = 0; i <= length; ++i){
                m_matrix[i][0] = -i-12;
            }
        }else if(std::is_same<T, char>::value){
            m_matrix[0][0] = 'F';
            for(int j = 1; j <= width; ++j){
                m_matrix[0][j] = 'I';
            }

            for(int i = 1; i <= length; ++i){
                m_matrix[i][0] = 'D';
            }
        }
    };
	
	void set_entry(int i, int j, T value){
		m_matrix[i+1][j+1] = value;
	}	

	T get_entry(int i, int j){

        /*if((std::is_same<T, int>::value) && (!gap_opening_penalty)) {
            if ((i == -1) && (j >= 0)) {
                return -j - 1;
            } else if (i == -1) {
                return 0;
            } else if ((j == -1) && (i >= 0)) {
                return -i - 1;
            } else if (j == -1) {
                return 0;
            } else {
                return m_matrix[i][j];
            }*/

        return m_matrix[i+1][j+1];

        /*}else if(std::is_same<T,char>::value){
            if((i == -1) && (j >= 0)){
                return 'I';
            }else if(i == -1){
                return 'F';
            }else if((j == -1) && (i >= 0)){
                return 'D';
            }else if(j == -1){
                return 'F';
            }else{
                return m_matrix[i][j];
            }
        }*/
        /*else if((std::is_same<T, int>::value) && (gap_opening_penalty)){
            if ((i == -1) && (j >= 0)) {
                return (-j - 12);
            } else if (i == -1) {
                return 0;
            } else if ((j == -1) && (i >= 0)) {
                return (-i - 12);
            } else if (j == -1) {
                return 0;
            } else {
				return m_matrix[i][j];
			}
		}else{
            return m_matrix[i][j];
        }*/
	}


	int get_length(){
		return m_length;
	}

	int get_width(){
		return m_width;
	}

	void print(std::string name){
		std::cout<<name<<std::endl;
		for(int i = 0; i < this->get_length(); ++i){
			for(int j = 0; j < this->get_width(); ++j){
				/*std::cout<< name<<"[ "<<i<<" ][ "<<j<<"] = "*/ std::cout<< this->get_entry(i,j)<< " ";
			}
			std::cout<<std::endl;
		}
	}
};