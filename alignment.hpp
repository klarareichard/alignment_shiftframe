#pragma once 
#include <unordered_map>
#include "Sequence.hpp"
#include <vector>
#include "Matrix.hpp"
#include "ScoreMatrix.hpp"
#include <algorithm>
#include <assert.h>

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
	Matrix<char> last_entry; 
	Matrix<int> frame;

	std::vector<Sequence> sequences;
	ScoreMatrix distance;

	Alignment(Sequence seq1, Sequence seq2, int gap_opening_penalty, int gap_extension_penalty, int delta): m_seq(seq1)
	, m_refseq(seq2), m_gop(gap_opening_penalty), m_gep(gap_extension_penalty), m_delta(delta), D(std::vector<Matrix<int>>(3, Matrix<int>(seq1.length(), seq2.length())))
	, P(std::vector<Matrix<int>>(3, Matrix<int>(seq1.length(), seq2.length()))), Q(std::vector<Matrix<int>>(3, Matrix<int>(seq1.length(), seq2.length())))
	, sequences(std::vector<Sequence>(3, Sequence(""))), last_entry(Matrix<char>(seq1.length(), seq2.length())){

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

	void print_dp_matrix(int frame){
		D[frame].print("D");
	}

	void print_score_matrix(){
		distance.print();
	}
	void print_p_matrix(int frame){
		P[frame].print("P");
	}

	void print_q_matrix(int frame){
		Q[frame].print("Q");
	}

	void print_bt_matrix(){
		last_entry.print("Backtrace");
	}

	void smith_waterman_update(int frame, int i, int j){


		int set_value = std::max( D[frame].get_entry(i-1,j) - full_gap_penalty, P[frame].get_entry(i-1,j) - m_gep);
		P[frame].set_entry(i, j, set_value);

		set_value = std::max( D[frame].get_entry(i,j-1) - full_gap_penalty, Q[frame].get_entry(i,j-1) - m_gep);
		Q[frame].set_entry(i, j, set_value);

		int max_array[3] = {D[frame].get_entry(i-1,j-1) + distance.getDistance(sequences[frame][i], m_refseq[j]), P[frame].get_entry(i,j), Q[frame].get_entry(i,j)};
		const int N = sizeof(max_array) / sizeof(int);
		set_value = *std::max_element(max_array, max_array+N);
		int last_move = std::distance(max_array, std::max_element(max_array, max_array+N));
		std::cout<<" last_move = "<< last_move<<std::endl;
		char last_move_c;
		if(last_move == 0){
			last_move_c = 'M';
		}else if(last_move == 1){
			last_move_c = 'D';
		}else if(last_move == 2){
			last_move_c = 'I';
		}else{
			assert(0);
		}
		D[frame].set_entry(i, j, set_value);
		last_entry.set_entry(i, j, last_move_c);
		frame.set_entry(i, j, frame);
	}

	void frame_shift_update(int curr_frame, int update_frame, int i, int j){
		
		int t1 = std::max(D[update_frame].get_entry(i-1,j) - full_gap_penalty, P[update_frame].get_entry(i-1,j) - m_gep);
		int t2 = std::max(D[update_frame].get_entry(i,j-1) - full_gap_penalty, Q[update_frame].get_entry(i,j-1) - m_gep);

		int max_array[3] = {D[update_frame].get_entry(i-1,j-1) + distance.getDistance(m_seq[i], m_refseq[j]), t1, t2};
		const int N = sizeof(max_array) / sizeof(int);
		int t3 = *std::max_element(max_array, max_array+N);
		int last_move = std::distance(max_array, std::max_element(max_array, max_array+N));
		char last_move_c;
		if(last_move == 0){
			last_move_c = 'M';
		}else if(last_move == 1){
			last_move_c = 'D';
		}else if(last_move == 2){
			last_move_c = 'I';
		}else{
			assert(0);
		}

		if(t3 - m_delta > D[curr_frame].get_entry(i,j)){
			P[curr_frame].set_entry(i,j, t1 - m_delta);
			Q[curr_frame].set_entry(i,j, t2 - m_delta);
			D[curr_frame].set_entry(i,j, t3 - m_delta);
			last_entry.set_entry(i, j, last_move_c);
			frame.set_entry(update_frame);
		}

		
	}

	void back_trace(){
		int first_row_v = m_seq.length()-1;
		int first_col_v = m_refseq.length()-1;
		std::string seq = "";
		std::string ref_seq = "";
		while((first_col_v >= 0) && (first_row_v >= 0)){
			char action = last_entry.get_entry(first_row_v, first_col_v);
			if(action == 'D'){
				ref_seq += '_';
				seq += m_seq[first_row_v];
				first_row_v--;
			}else if(action == 'I'){
				seq += '_';
				ref_seq += m_refseq[first_col_v];
				first_col_v--;
			}else if(action == 'M'){
				seq += m_seq[first_row_v];
				ref_seq += m_refseq[first_col_v];
				first_col_v--;
				first_row_v--;
			}
		}
		reverse(seq.begin(), seq.end());
		reverse(ref_seq.begin(), ref_seq.end());
		std::string rev_seq = "";
		std::string rev_ref_seq = "";
		for(int i = seq.length()-1; i >= 0; --i){
			rev_seq.push_back(seq[i]);
			rev_ref_seq.push_back(ref_seq[i]);
		}
		for(int i = 0; i < rev_seq.length(); ++i){
			std::cout<<" seq = "<< seq[i]<< std::endl;
			std::cout<<" ref_seq = "<< ref_seq[i]<<std::endl;
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

	void compute_smith_waterman_matrices(){
		for(int f = 0; f < 3; f++ ){
			compute_smith_waterman_matrices(f);
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