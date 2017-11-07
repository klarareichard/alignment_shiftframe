#include <unordered_map>

template<typename Matrix, typename Sequence> class Alignment{

	Matrix m_dp; 
	Sequence m_seq1; 
	Sequence m_seq2;
	int m_gop; //gap opening penalty
	int m_gep; // gap extension penalty
	int full_gap_penalty = m_gop + m_gep;

	Alignment(dp_matrix, seq1, seq2, gap_opening_penalty, gap_extension_penalty): 
	m_dp(dp_matrix), m_seq1(seq1), m_gop(gap_opening_penalty), m_gep(gap_extension_penalty){}; 

	// use score matrix that is by default 4*4 and in the order ACGT
	// and which is if protein 
	void align_with_frameshifts(Matrix Score){

		Matrix P1; 
		Matrix Q1; 
		Matrix D1;

		Matrix P2;
		Matrix Q2; 
		Matrix D2;

		for(int i = 0; i < width; ++i){
			for(int j = 0; j < width; ++j){
				P1[i][j] = min( D1[i-1][j] + full_gap_penalty, P1[i-1][j] + u);
				Q1[i][j] = min( D1[i][j-1] + full_gap_penalty, Q1[i][j-1] + u);
				D1[i][j] = min( D1[i-1][j-1] )
			}
		}


	}

};