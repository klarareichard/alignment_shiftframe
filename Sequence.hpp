#pragma once 
#include "assert.h"
#include <string>
#include <algorithm>
#include <iostream>
class Sequence{
		public:
		std::string m_seq;

		char operator[](int i){
			if(i > -1){
				return m_seq[i];
			}else{
				return 0;
			}
		}
		Sequence(std::string s):m_seq(s){};
		Sequence(): m_seq(""){};
		Sequence shift(int i){
			return m_seq.substr(i, m_seq.length());
		}

		std::string get_string(){
			return m_seq;
		}

		char get_entry(int i){
			assert(i < m_seq.length());
			return m_seq[i];
		}

		int length(){
			return m_seq.length();
		}

		Sequence substr(int i){
			return m_seq.substr(i);
		}

		Sequence substr(int i, int j){
			return m_seq.substr(i, j);
		}

		Sequence reverse(){
			std::reverse(m_seq.begin(), m_seq.end());
			return m_seq;
		}

		void append(char c){
			m_seq+= c;
		}

		void print(std::string name){
			for(int i = 0; i < m_seq.length(); ++i){
				std::cout<<name<<"[ "<<i<< "] = "<< m_seq[i]<<std::endl;
			}
		}
		//Sequence complement()


};