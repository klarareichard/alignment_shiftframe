template <typename T> class Sequence{

		std::string<T> m_seq;
		void shift(int i){
			m_seq = m_seq.substr(i, m_seq.length());
		}

		std::string<T> get_string(){
			return m_seq;
		}

		char get_entry(int i){
			assert(i < m_seq.length());
			return m_seq[i];
		}


};