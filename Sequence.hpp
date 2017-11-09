#pragma once 
#include "assert.h"
#include <string>
#include <algorithm>
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

		Sequence reverse(){
			std::reverse(m_seq.begin(), m_seq.end());
			return m_seq;
		}


};