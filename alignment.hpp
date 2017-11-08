#include <unordered_map>
#include "Sequence.hpp"

template<typename Matrix, typename Sequence, typename ScoreMatrix> class Alignment{

	Matrix m_dp; 
	Sequence m_refseq; 
	Sequence m_seq;
	int m_gop; //gap opening penalty
	int m_gep; // gap extension penalty
	int full_gap_penalty = m_gop + m_gep;
	int m_delta;


	ScoreMatrix distance;
	std::vector<Matrix> D;
	std::vector<Matrix> P; 
	std::vector<Matrix> Q;
	std::vector<Sequence> sequences;

	Alignment(seq1, seq2, gap_opening_penalty, gap_extension_penalty, int delta): m_seq(seq1)
	, m_refseq(seq2) m_gop(gap_opening_penalty), m_gep(gap_extension_penalty), m_delta(delta), D(std::vector<Matrix>(Matrix(), 3))
	, P(std::vector<Matrix>(Matrix(), 3)), Q(std::vector<Matrix>(Matrix(), 3)), sequences(std::vector<Sequence>(Sequence(), 3)){

		for(int i = 0; i < 3; ++i){
			sequences[i] = seq1.shift(i);
		}
	};

	std::vector<int> getOtherIndices(int i){

		std::vector<int> indices;
		if(i == 0){
			indices.push_back(1);
			indices.push_back(2);
		}
		if(i == 1){
			indices.push_back(0);
			indices.push_back(2);
		}
		if(i == 2){
			indices.push_back(0);
			indices.push_back(1);
		}

		return indices;
	} 

	void smith_waterman_update(int frame, int i, int j){


		int set_value = min( D[frame].get_entry(i-1,j) - full_gap_penalty, P[frame].get_entry(i-1,j) - gap_extension_penalty);
		P[frame].set_entry(i, j, set_value);

		set_value = min( D[frame].get_entry(i,j-1) - full_gap_penalty, Q[frame].get_entry(i,j-1) - gap_extension_penalty);
		Q[frame].set_value(i, j, set_value);

		set_value = min( D[frame].get_entry(i-1,j-1) - distance.getDistance(sequences[frame][i], ref_seq[j]), P[frame].get_entry(i,j), Q[frame].get_entry(i,j),0);
		D[frame].set_value(i, j, set_value);
	}

	void frame_shift_update(int curr_frame, int update_frame, int i, int j){
		
		t1 = max(D[update_frame].get_entry(i-1,j) - full_gap_penalty, P[update_frame].get_entry(i-1,j) - gap_extension_penalty);
		t2 = max(D[update_frame].get_entry(i,j-1) - full_gap_penalty, Q[update_frame].get_entry(i,j-1) - gap_extension_penalty);
		t3 = max(D[update_frame].get_entry(i-1,j-1) - distance.getDistance(seq[i], ref_seq[j]), t1, t2, 0);

		if(t3 - delta > D[curr_frame].get_entry(i,j)){
			P[curr_frame].set_entry(i,j, t1 - m_delta);
			Q[curr_frame].set_entry(i,j, t2 - m_delta);
			D[curr_frame].set_entry(i,j, t3 - m_delta);
		}

		
	}


	void extend_dp_matrix(int frame, int i, int j){

		Sequence seq = m_seq.shift(frame);
		Sequence ref = ref_seq;

		std::vector<int> otherIndices = getOtherIndices(frame);
		int i1 = otherIndices[0];
		int i2 = otherIndices[1];

		smith_waterman_update(frame, i, j);
		frame_shift_update(frame, i1, i, j);
		frame_shift_update(frame, i2, i, j);
	}

	void compute_smith_waterman_matrices(){

		for(int i = 0; i < m_seq.length(); ++i){
			for(int j = 0; j < m_refseq.length(); ++j){
				smith_waterman_update();
			}
		}
	}

	void compute_all_dp_matrices(){

		Sequence ref_seq = m_refseq;
		Sequence seq = m_seq;

		for(int i = 0; i < seq.length(); ++i){
			for(int j = 0; j < ref_seq.length(); ++j){
				extend_dp_matrix(0);
				extend_dp_matrix(1);
				extend_dp_matrix(2);
			}
		}
	}

};