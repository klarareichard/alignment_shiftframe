#pragma once 
#include <unordered_map>
#include "Sequence.hpp"
#include <vector>
#include "Matrix.hpp"
#include "ScoreMatrix.hpp"

class Alignment{
public:
	Sequence m_refseq; 
	Sequence m_seq;
	int m_gop; //gap opening penalty
	int m_gep; // gap extension penalty
	int full_gap_penalty = m_gop + m_gep;
	int m_delta;

	std::vector<Matrix<int>> D;
	std::vector<Matrix<int>> P; 
	std::vector<Matrix<int>> Q;
	std::vector<Sequence> sequences;
	ScoreMatrix distance;

	Alignment(Sequence seq1, Sequence seq2, int gap_opening_penalty, int gap_extension_penalty, int delta): m_seq(seq1)
	, m_refseq(seq2), m_gop(gap_opening_penalty), m_gep(gap_extension_penalty), m_delta(delta), D(std::vector<Matrix<int>>(3, Matrix<int>(seq1.length(), seq2.length())))
	, P(std::vector<Matrix<int>>(3, Matrix<int>(seq1.length(), seq2.length()))), Q(std::vector<Matrix<int>>(3, Matrix<int>(seq1.length(), seq2.length()))), sequences(std::vector<Sequence>(3, Sequence(""))){

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


		int set_value = std::max( D[frame].get_entry(i-1,j) - full_gap_penalty, P[frame].get_entry(i-1,j) - m_gep);
		P[frame].set_entry(i, j, set_value);

		set_value = std::max( D[frame].get_entry(i,j-1) - full_gap_penalty, Q[frame].get_entry(i,j-1) - m_gep);
		Q[frame].set_entry(i, j, set_value);

		int d1 = std::max(D[frame].get_entry(i-1,j-1) - distance.getDistance(sequences[frame][i], m_refseq[j]), P[frame].get_entry(i,j));
		int d2 = std::max(Q[frame].get_entry(i,j),0);
		set_value = std::max( d1, d2);
		D[frame].set_entry(i, j, set_value);
	}

	void frame_shift_update(int curr_frame, int update_frame, int i, int j){
		
		int t1 = std::max(D[update_frame].get_entry(i-1,j) - full_gap_penalty, P[update_frame].get_entry(i-1,j) - m_gep);
		int t2 = std::max(D[update_frame].get_entry(i,j-1) - full_gap_penalty, Q[update_frame].get_entry(i,j-1) - m_gep);
		int t31 = std::max(D[update_frame].get_entry(i-1,j-1) - distance.getDistance(m_seq[i], m_refseq[j]), t1);
		int t32 = std::max(t2, 0);
		int t3 = std::max(t31, t32);

		if(t3 - m_delta > D[curr_frame].get_entry(i,j)){
			P[curr_frame].set_entry(i,j, t1 - m_delta);
			Q[curr_frame].set_entry(i,j, t2 - m_delta);
			D[curr_frame].set_entry(i,j, t3 - m_delta);
		}

		
	}


	void extend_dp_Matrix(int frame, int i, int j){

		Sequence seq = m_seq.shift(frame);
		Sequence ref = m_refseq;

		std::vector<int> otherIndices = getOtherIndices(frame);
		int i1 = otherIndices[0];
		int i2 = otherIndices[1];

		smith_waterman_update(frame, i, j);
		frame_shift_update(frame, i1, i, j);
		frame_shift_update(frame, i2, i, j);
	}

	void compute_smith_waterman_matrices(int frame){

		for(int i = 0; i < m_seq.length(); ++i){
			for(int j = 0; j < m_refseq.length(); ++j){
				smith_waterman_update(frame, i, j);
			}
		}
	}

	void compute_all_dp_matrices(){

		Sequence ref_seq = m_refseq;
		Sequence seq = m_seq;

		for(int i = 0; i < seq.length(); ++i){
			for(int j = 0; j < ref_seq.length(); ++j){
				extend_dp_Matrix(0, i, j);
				extend_dp_Matrix(1, i, j);
				extend_dp_Matrix(2, i, j);
			}
		}
	}

};