#pragma once
#include <unordered_map>
#include "Sequence.hpp"
#include <vector>
#include "Matrix.hpp"
#include "ScoreMatrix.hpp"
#include <algorithm>
#include <assert.h>
#include <limits>
#include "Translator.hpp"


class Alignment_imp{
public:
    Sequence m_refseq;
    Sequence m_seq;
    std::string aligned_seq;
    std::string aligned_ref_seq;
    double m_gop; //gap opening penalty
    double m_gep; // gap extension penalty
    double m_score;
    double m_delta;

    Matrix<double> C;
    Matrix<double> D;
    Matrix<double> I;
    Matrix<char> last_entry;
    Matrix<char> last_entry_d;
    Matrix<char> last_entry_i;
    Matrix<char> amino;
    Translator t;
    ScoreMatrix distance;
    std::string al_result;
    std::string ref_result;

    Alignment_imp(Sequence seq, Sequence ref_seq, double gop, double gep, double delta): m_seq(seq), m_refseq(ref_seq),
                                                                      m_gop(gop), m_gep(gep),
                                                                      C(Matrix<double>(m_seq.length(), m_refseq.length())),
                                                                      D(Matrix<double>(m_seq.length(), m_refseq.length())),
                                                                      I(Matrix<double>(m_seq.length(), m_refseq.length())),
                                                                      last_entry(Matrix<char>(m_seq.length(), m_refseq.length())),
                                                                      m_delta(delta),
                                                                      amino(Matrix<char>(m_seq.length(), m_refseq.length())),
                                                                      last_entry_d(m_seq.length(), m_refseq.length()),
                                                                      last_entry_i(m_seq.length(), m_refseq.length())
                                                                      {};


    double dna_gap(int gap_size){
        double score = (double)((double)(-m_gep*(double)gap_size)/(double)3.0) - (double) m_gop;
        if((gap_size % 3 ) != 0){
            score = -std::numeric_limits<double>::infinity();
        }
        //std::cout<<"score = "<<score<<std::endl;
        return score;
    }
    double pro_gap(int gap_size){
        return (double) (-m_gep * (double)gap_size) -(double) m_gop;
    }
    void update_I(int i, int j){
        assert(j > 0);
        double update_score = std::max(I.get_entry(i, j-1), C.get_entry(i, j-1) - m_gop) - m_gep;
        I.set_entry(i, j, update_score);
        if(I.get_entry(i, j-1) > C.get_entry(i, j-1)){
            last_entry_i.set_entry(i, j, 'I');
        }else{
            last_entry_i.set_entry(i, j, 'C');
        }

    }



    std::pair<int,double> get_max(const std::vector<double> &v){
        double max_val = -std::numeric_limits<double>::max();
        int arg_max = 0;
        for(int i = 0; i < v.size(); ++i){
            double val = v[i];
            if(val > max_val){
                max_val = val;
                arg_max = i;
            }
        }
        return std::make_pair(arg_max, max_val);
    }

    std::pair<char,double> get_max_score(std::string s, char comp_amino){
        assert(s.length() <= 4);
        assert(s.length() >=2);
        //std::vector<int> max_vec;
        std::vector<char> nucleotides;
        nucleotides.push_back('A');
        nucleotides.push_back('G');
        nucleotides.push_back('C');
        nucleotides.push_back('T');
        char max_amino_acid;

        double max = -std::numeric_limits<double>::max();

        if(s.length() == 2){
            for(int i = 0; i < nucleotides.size(); ++i){
                std::string concat = std::string();
                concat += nucleotides[i];
                concat += s;
                //std::cout<<"concat = "<<concat<<std::endl;
                for(int i = 0; i < concat.length(); ++i){
                    assert(!isspace(concat[i]));
                }
                char amino_acid = t.translate(concat);
                if(distance.getDistance(amino_acid, comp_amino) > max){
                    max = distance.getDistance(amino_acid, comp_amino);
                    max_amino_acid = amino_acid;
                }

            }
            for(int i = 0; i < nucleotides.size(); ++i){
                std::string concat = std::string();
                concat += s;
                concat += nucleotides[i];
                char amino_acid = t.translate(concat);
                if(distance.getDistance(amino_acid, comp_amino) > max){
                    max = distance.getDistance(amino_acid, comp_amino);
                    max_amino_acid = amino_acid;
                }
            }
            max = (double) max - (double) m_delta;
        }else if(s.length() == 3){
            char amino_acid = t.translate(s);
            if(distance.getDistance(amino_acid, comp_amino) > max){
                max = distance.getDistance(amino_acid, comp_amino);
                max_amino_acid = amino_acid;
            }

        }else if(s.length() == 4){
            std::vector<std::string> codons;
            codons.push_back(s.substr(0, 3));
            codons.push_back(s.substr(1,3));

            for(int i = 0; i < codons.size(); ++i){
                char amino_acid = t.translate(codons[i]);
                if(distance.getDistance(amino_acid, comp_amino) > max){
                    max = distance.getDistance(amino_acid, comp_amino);
                    max_amino_acid = amino_acid;
                }
            }
            max = (double) max - (double) m_delta;
        }
        return std::make_pair(max_amino_acid, (double) max);

    }
    void update_D(int i, int j){
        assert(i >=3);
        double update_score = std::max(D.get_entry(i-3, j), C.get_entry(i-3, j) - m_gop) - m_gep;
        D.set_entry(i, j, update_score);
        if(D.get_entry(i-3, j) > (C.get_entry(i-3, j) -m_gop)){
            last_entry_d.set_entry(i, j, 'D');
        }else{
            last_entry_d.set_entry(i, j, 'C');
        }

    }
    void update_C(int i, int j){
        double update_score;
        int arg_max;
        if(i ==2){
            std::string sub_seq = (m_seq.get_string()).substr(0,2);
            auto pair = get_max_score(sub_seq, m_refseq[j]);
            update_score = std::max(I.get_entry(2, j), C.get_entry(0, j-1)+ pair.second);
            arg_max = 0;
            if(C.get_entry(0, j-1)+ get_max_score(sub_seq, m_refseq[j]).second > I.get_entry(2,j)){
                arg_max = 1;
            }
            if(arg_max == 0){
                last_entry.set_entry(i, j, 'I');
                amino.set_entry(i,j, pair.first);
            }else if(arg_max == 1){
                last_entry.set_entry(i, j, 'C');
                amino.set_entry(i,j, pair.first);
            }else{
                assert(0);
            }
            C.set_entry(i, j, update_score);
        }else if(i ==3){
            std::string sub_seq = (m_seq.get_string()).substr(0,3);
            std::vector<double> possible_entries;
            possible_entries.push_back(D.get_entry(3,j));
            possible_entries.push_back(I.get_entry(3,j));

            possible_entries.push_back(C.get_entry(0, j-1) + get_max_score(sub_seq, m_refseq[j]).second);
            auto pair = get_max(possible_entries);
            update_score = pair.second;
            arg_max = pair.first;
            if(arg_max == 0){
                last_entry.set_entry(i, j, 'D');
            }else if(arg_max == 1){
                last_entry.set_entry(i, j, 'I');
            }else if(arg_max == 2){
                last_entry.set_entry(i, j, 'E');
            }else{
                assert(0);
            }
            C.set_entry(i, j, update_score);
        }else{
            std::string sub_seq1 = m_seq.get_string().substr(i-1,2);
            std::string sub_seq2 = m_seq.get_string().substr(i-2,3);
            std::string sub_seq3 = m_seq.get_string().substr(i-3,4);

            std::vector<double> possible_entries;
            possible_entries.push_back(D.get_entry(i, j));
            possible_entries.push_back(I.get_entry(i, j));
            possible_entries.push_back(C.get_entry(i-2, j-1) + get_max_score(sub_seq1, m_refseq[j]).second);
            possible_entries.push_back(C.get_entry(i-3, j-1)+ get_max_score(sub_seq2, m_refseq[j]).second);
            possible_entries.push_back(C.get_entry(i-4, j-1)+ get_max_score(sub_seq3, m_refseq[j]).second);
            auto pair = get_max(possible_entries);
            update_score = pair.second;
            arg_max = pair.first;
            if(arg_max == 0){
                last_entry.set_entry(i, j, 'D');
            }else if(arg_max == 1){
                last_entry.set_entry(i, j, 'I');
            }else if(arg_max == 2){
                last_entry.set_entry(i, j, 'C');
            }else if(arg_max == 3){
                last_entry.set_entry(i, j, 'E');
            }else if(arg_max == 4){
                last_entry.set_entry(i, j, 'F');
            }
        }

        C.set_entry(i, j, update_score);

    }

    void initialize() {
        C.set_entry(0, 0, 0.0);
        last_entry.set_entry(0, 0, 'G');
        for (int i = 1; i < m_seq.length(); i++) {
            C.set_entry(i, 0, dna_gap(i));
            last_entry.set_entry(i, 0, 'G');
        }

        for (int j = 1; j < m_refseq.length(); j++) {
            C.set_entry(0, j, pro_gap(j));
            last_entry.set_entry(0, j, 'H');
        }
        for (int j = 1; j < m_refseq.length(); j++) {
            C.set_entry(1, j, -std::numeric_limits<double>::infinity());
        }

        for(int i = 0; i < m_seq.length(); ++i){
            I.set_entry(i, 0, -std::numeric_limits<double>::infinity());
        }

        for(int j = 1; j < m_refseq.length(); ++j){
            update_I(1, j);
        }

        for(int j = 1; j < m_refseq.length(); ++j){
            update_I(2,j);
            update_C(2, j);
        }

        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < m_refseq.length(); ++j){
                D.set_entry(i, j, -std::numeric_limits<double>::infinity());
            }
        }

        for(int j = 0; j < m_refseq.length(); ++j){
            update_D(3,j);
        }

        for(int j =1; j < m_refseq.length(); ++j){
            update_I(3, j);
            update_C(3, j);
        }

    }

    void update(int i, int j){
        assert(j > 0);
        assert(i > 3);
        update_D(i, j);
        update_I(i, j);
        update_C(i, j);
    }

    void compute_matrices(){
        for(int i = 4; i < m_seq.length(); ++i){
            for(int j = 1; j < m_refseq.length(); ++j){
                update(i, j);
            }
        }
    }

    std::string get_al_result(){
        return al_result;
    }

    double get_score(){
        return m_score;
    }

    std::string get_ref_result(){
        return ref_result;
    }

    void back_trace(){
        int first_row = C.get_length()-1;
        int first_col = C.get_width()-1;
        std::string aligned_seq;
        std::string reference_seq;
        m_score = C.get_entry(first_row, first_col);
        int next_matrix = 2;
        while(first_row >= 0 || first_col >=0){
            char action;
            if(next_matrix == 2) {
                action = last_entry.get_entry(first_row, first_col);

                if (action == 'D') {
                    next_matrix = 0;

                } else if (action == 'I') {

                    next_matrix = 1;
                } else if (action == 'C') {
                    std::string sub_seq = m_seq.get_string().substr(first_row - 1, 2);
                    aligned_seq += get_max_score(sub_seq, m_refseq[first_col]).first;
                    //std::cout<<"sub_seq= "<<sub_seq<<std::endl;
                    //std::cout<<"amino = "<<m_refseq[first_col]<<std::endl;
                    //std::cout<<"score = "<<get_max_score(sub_seq, m_refseq[first_col]).second<<std::endl;
                    reference_seq += m_refseq[first_col];
                    first_col--;
                    first_row -= 2;
                } else if (action == 'E') {
                    std::string sub_seq = m_seq.get_string().substr(first_row - 2, 3);
                    aligned_seq += get_max_score(sub_seq, m_refseq[first_col]).first;
                    //std::cout<<"sub_seq= "<<sub_seq<<std::endl;
                    //std::cout<<"amino = "<<m_refseq[first_col]<<std::endl;
                    //std::cout<<"score = "<<get_max_score(sub_seq, m_refseq[first_col]).second<<std::endl;
                    reference_seq += m_refseq[first_col];
                    first_col--;
                    first_row -= 3;
                } else if (action == 'F') {
                    std::string sub_seq = m_seq.get_string().substr(first_row - 3, 4);
                    aligned_seq += get_max_score(sub_seq, m_refseq[first_col]).first;
                    //std::cout<<"sub_seq= "<<sub_seq<<std::endl;
                    //std::cout<<"amino = "<<m_refseq[first_col]<<std::endl;
                    //std::cout<<"score = "<<get_max_score(sub_seq, m_refseq[first_col]).second<<std::endl;
                    reference_seq += m_refseq[first_col];
                    first_col--;
                    first_row -= 4;
                } else if (action == 'G') {
                    if(first_row >= 3)
                    {
                        std::string sub_seq = m_seq.get_string().substr(first_row - 2, 3);
                        aligned_seq += t.translate(sub_seq);
                        reference_seq += '_';
                        first_row -= 3;
                    }else if(first_row == 2){
                        std::string sub_seq = m_seq.get_string().substr(0, first_row);
                        aligned_seq += get_max_score(sub_seq, 'L').first;
                        reference_seq += '_';
                        first_row -= first_row;
                    }else{
                        first_row --;
                    }
                } else if (action == 'H') {
                    aligned_seq += '_';
                    reference_seq += m_refseq[first_col];
                    first_col--;
                } else {
                    assert(0);
                }
            }else if(next_matrix == 1){
                action = last_entry_i.get_entry(first_row, first_col);
                aligned_seq += '_';
                reference_seq += m_refseq[first_col];
                first_col--;
                if(action == 'I'){
                    next_matrix = 1;
                }else if(action == 'C'){
                    next_matrix = 2;
                }
            }else if(next_matrix == 0){
                action = last_entry_d.get_entry(first_row, first_col);
                std::string sub_seq = m_seq.get_string().substr(first_row - 2, 3);
                aligned_seq += get_max_score(sub_seq, m_refseq[first_col]).first;
                //std::cout<<"sub_seq= "<<sub_seq<<std::endl;
                //std::cout<<"amino = "<<m_refseq[first_col]<<std::endl;
                //std::cout<<"score = "<<get_max_score(sub_seq, m_refseq[first_col]).second<<std::endl;
                reference_seq += '_';
                first_row -= 3;

                if(action == 'D'){
                    next_matrix = 0;
                }else if(action == 'C'){
                    next_matrix = 2;
                }
            }

        }
        reverse(aligned_seq.begin(), aligned_seq.end());
        reverse(reference_seq.begin(), reference_seq.end());

        al_result = aligned_seq;
        ref_result = reference_seq;

    }

    void print_D(){
        D.print("D");
    }

    void print_C(){
        C.print("C");
    }

    void print_I(){
        I.print("I");
    }

    void print_bt(){
        last_entry.print("Backtrace");
    }
    void print_bt_i(){
        last_entry_i.print("Backtrace_i");
    }

    void print_bt_d(){
        last_entry_d.print("Backtrace_d");
    }

    std::string get_ref_seq(){
            return m_refseq.get_string();
    }

    std::string get_seq(){
        return m_seq.get_string();
    }
};