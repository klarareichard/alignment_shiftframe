#pragma once 
#include "assert.h"
#include <string>
class Sequence{
		public:
		std::string m_seq;

		char operator[](int i){
			return m_seq[i];
		}
		Sequence(std::string s):m_seq(s){};
		
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


};