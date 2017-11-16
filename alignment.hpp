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
	std::string aligned_seq;
	std::string aligned_ref_seq;
	int m_gop; //gap opening penalty
	int m_gep; // gap extension penalty
	int full_gap_penalty = m_gop + m_gep;
	int m_delta;
    int m_score;

	std::vector<Matrix<int>> D;
	std::vector<Matrix<int>> P; 
	std::vector<Matrix<int>> Q;
	std::vector<Matrix<char>> last_entry;
	Matrix<int> m_frame;
	std::vector<int> lengths;


	std::vector<Sequence> sequences;
	ScoreMatrix distance;

	Alignment(Sequence seq1, Sequence seq2, std::vector<Sequence> in_sequences, int gap_opening_penalty, int gap_extension_penalty, int delta): m_seq(seq1)
	, m_refseq(seq2), m_gop(gap_opening_penalty), m_gep(gap_extension_penalty), m_delta(delta), sequences(in_sequences), m_score(9){

        for(int i = 0; i < sequences[0].length(); ++i){
            assert(!isspace(sequences[0].get_entry(i)));
        }
        for(int i = 0; i < sequences[1].length(); ++i){
            assert(!isspace(sequences[1].get_entry(i)));
        }
        for(int i = 0; i < sequences[2].length(); ++i){
            assert(!isspace(sequences[2].get_entry(i)));
        }


        /*D(std::vector<Matrix<int>>(3, Matrix<int>(m_seq.length(), m_refseq.length())))
                , P(std::vector<Matrix<int>>(3, Matrix<int>(m_seq.length(), m_refseq.length()))), Q(std::vector<Matrix<int>>(3, Matrix<int>(m_seq.length(), m_refseq.length())))
                , sequences(in_sequences), last_entry(std::vector<Matrix<char>>(3, Matrix<char>(m_seq.length(), m_refseq.length()))), m_frame(std::vector<Matrix<int>>(3, Matrix<int>(m_seq.length(), m_refseq.length())))
                , aligned_seq(""), aligned_ref_seq("")*/



        Matrix<int> D0(sequences[0].length(), m_refseq.length(), true);
        Matrix<int> D1(sequences[0].length(), m_refseq.length(), true);
        Matrix<int> D2(sequences[0].length(), m_refseq.length(), true);

        D.push_back(D0);
        D.push_back(D1);
        D.push_back(D2);

        Matrix<int> P0(sequences[0].length(), m_refseq.length(), true);
        Matrix<int> P1(sequences[0].length(), m_refseq.length(), true);
        Matrix<int> P2(sequences[0].length(), m_refseq.length(), true);

        P.push_back(P0);
        P.push_back(P1);
        P.push_back(P2);

        Matrix<int> Q0(sequences[0].length(), m_refseq.length(), true);
        Matrix<int> Q1(sequences[0].length(), m_refseq.length(), true);
        Matrix<int> Q2(sequences[0].length(), m_refseq.length(), true);

        Q.push_back(Q0);
        Q.push_back(Q1);
        Q.push_back(Q2);


        Matrix<char> last_entry0(sequences[0].length(), m_refseq.length());
        Matrix<char> last_entry1(sequences[0].length(), m_refseq.length());
        Matrix<char> last_entry2(sequences[0].length(), m_refseq.length());

        last_entry.push_back(last_entry0);
        last_entry.push_back(last_entry1);
        last_entry.push_back(last_entry2);

        Matrix<int> m_frame(sequences[0].length(), m_refseq.length());
        //print_dp_matrix(0);
        distance.readBlosum62("/Users/klara/alignment_shiftframe/Blosum62.txt");
       // distance.print();
        /*std::cout<< "D length = "<<D[0].get_length()<<std::endl;
        std::cout<< "D width = "<<D[0].get_width()<<std::endl;
        std::cout<< " width = "<<D[0].get_length()<<std::endl;
        std::cout<<"m_ref_seq = "<< m_refseq.get_string()<<std::endl;*/
        for(int i = 0; i < m_refseq.length(); ++i){
            //std::cout<<"hi"<<std::endl;
            assert(!isspace(m_refseq.get_string()[i]));
        }
        /*std::cout<<"m_seq = "<<m_seq.get_string()<<std::endl;
        std::cout<<"seq_length = "<<m_seq.length()<<std::endl;
        std::cout<<"refseq_length = "<<m_refseq.length()<<std::endl;*/


        //std::cout<<"sequences[1] = "<< sequences[1].get_string()<<std::endl;
	};

    int get_score(){
        return m_score;
    }

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

	void print_bt_matrix(int frame){
		last_entry[frame].print("Backtrace");
	}

	void smith_waterman_update(int frame, int i, int j){


		int set_value = std::max( D[frame].get_entry(i-1,j) - full_gap_penalty, P[frame].get_entry(i-1,j) - m_gep);
		P[frame].set_entry(i, j, set_value);

		set_value = std::max( D[frame].get_entry(i,j-1) - full_gap_penalty, Q[frame].get_entry(i,j-1) - m_gep);
		Q[frame].set_entry(i, j, set_value);

		int max_array[3] = {D[frame].get_entry(i-1,j-1) + distance.getDistance(sequences[frame][i], m_refseq[j]), P[frame].get_entry(i,j), Q[frame].get_entry(i,j)};
        //int max_array[3] = {D[frame].get_entry(i-1,j-1) + distance.getDistance(sequences[frame][i], m_refseq[j]), D[frame].get_entry(i-1, j) - m_gep, D[frame].get_entry(i, j-1) -m_gep};

        //std::cout<<" i = "<< i<< ", j = "<<j<<std::endl;
        int val = max_array[0];
        //std::cout<<"max_arr[0] = "<<val<<std::endl;
        val = max_array[1];
        //std::cout<<"max_arr[1] = "<<val<<std::endl;
        val = max_array[2];
        //std::cout<<"max_arr[2] = "<<val<<std::endl;

        //std::cout<<"distance = "<< distance.getDistance(m_seq[i], m_refseq[j])<<std::endl;

        //std::cout<<" match "<<m_seq[i]<<" and "<<m_refseq[j]<<std::endl;
        //std::cout<<"max array of one is minus zero"

		const int N = sizeof(max_array) / sizeof(int);
		set_value = *std::max_element(max_array, max_array+N);
        //std::cout<<"set_value = "<<set_value<<std::endl;
		int last_move = std::distance(max_array, std::max_element(max_array, max_array+N));
		//std::cout<<" last_move = "<< last_move<<std::endl;
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
		last_entry[frame].set_entry(i, j, last_move_c);
		m_frame[frame].set_entry(i, j, frame);
	}

	void frame_shift_update(int curr_frame, int update_frame, int i, int j){
		
		int t1 = std::max(D[update_frame].get_entry(i-1,j) - m_gop, P[update_frame].get_entry(i-1,j) - m_gep);
		int t2 = std::max(D[update_frame].get_entry(i,j-1) - m_gop, Q[update_frame].get_entry(i,j-1) - m_gep);

		int max_array[3] = {D[update_frame].get_entry(i-1,j-1) + distance.getDistance(sequences[curr_frame][i], m_refseq[j]), t1, t2};
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
			last_entry[curr_frame].set_entry(i, j, last_move_c);
			m_frame.set_entry(i, j, update_frame);
		}else{
            m_frame.set_entry(i, j, curr_frame);
        }

		
	}

	void back_trace(int frame){

		Sequence al_seq = sequences[frame];
		int first_row_v = al_seq.length()-1;
		int first_col_v = m_refseq.length()-1;

        std::cout<<"score = "<<D[frame].get_entry(first_row_v, first_col_v)<<std::endl;
        m_score = D[frame].get_entry(first_row_v, first_col_v);
		std::string seq = "";
		std::string ref_seq = "";
		while((first_col_v >= 0) || (first_row_v >= 0)){
		//	std::cout<<"backtrace"<<std::endl;
			char action = last_entry[frame].get_entry(first_row_v, first_col_v);
		//	std::cout<<"action = "<<action<<std::endl;
			if(action == 'D'){
				ref_seq += '_';
				seq += al_seq[first_row_v];
				first_row_v--;
			}else if(action == 'I'){
				seq += '_';
				ref_seq += m_refseq[first_col_v];
				first_col_v--;
			}else if(action == 'M'){
				seq += al_seq[first_row_v];
				ref_seq += m_refseq[first_col_v];
				first_col_v--;
				first_row_v--;
			}else if(action == 'F'){
                first_col_v--;
                first_row_v--;
            }

		}
		reverse(seq.begin(), seq.end());
		reverse(ref_seq.begin(), ref_seq.end());


		aligned_seq = seq;
		aligned_ref_seq = ref_seq;

	}


	void extend_dp_Matrix(int frame, int i, int j){


		std::vector<int> otherIndices = getOtherIndices(frame);
		int i1 = otherIndices[0];
		int i2 = otherIndices[1];

		smith_waterman_update(frame, i, j);
		/*frame_shift_update(frame, i1, i, j);
		frame_shift_update(frame, i2, i, j);*/
	}

	void compute_all_dp_matrices(int frame){

		Sequence ref_seq = m_refseq;
		Sequence seq = m_seq;
		for(int i = 0; i < sequences[0].length(); ++i){
			for(int j = 0; j < ref_seq.length(); ++j){
				extend_dp_Matrix(0, i, j);
			}
		}

        for(int i = 0; i < sequences[1].length(); ++i){
            for(int j = 0; j < ref_seq.length(); ++j){
                extend_dp_Matrix(1, i, j);
            }
        }
        for(int i = 0; i < sequences[2].length(); ++i){
            for(int j = 0; j < ref_seq.length(); ++j){
                extend_dp_Matrix(2, i, j);
            }
        }


        //print_bt_matrix(frame);
        //print_dp_matrix(frame);
		int t1 = D[0].get_entry(sequences[0].length()-2, sequences[0].length()-2);
		int t2 = D[1].get_entry(sequences[1].length()-2, sequences[1].length()-2);
		int t3 = D[2].get_entry(sequences[2].length()-2, sequences[2].length()-2);

		int max_array[3] = {t1, t2, t3};
		const int N = sizeof(max_array) / sizeof(int);
		int max = *std::max_element(max_array, max_array+N);
		int max_element = std::distance(max_array, std::max_element(max_array, max_array+N));

        /*print_dp_matrix(max_element);
        print_p_matrix(max_element);
        print_q_matrix(max_element);
        print_bt_matrix(max_element);*/

		back_trace(max_element);



	}

	std::string get_aligned_seq(){
		return aligned_seq;
	}

	std::string get_aligned_ref_seq(){
		return aligned_ref_seq;
	}





};