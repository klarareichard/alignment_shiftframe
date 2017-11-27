//#include "alignment.hpp"
#include "Matrix.hpp"
#include "ScoreMatrix.hpp"
#include "MatrixReader.hpp"
#include "Translator.hpp"
#include "InputReader.hpp"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include "ScoreMatrix.hpp"
#include <iostream>
#include "alignment_global.hpp"
#include "alignment.hpp"
#include <gtest/gtest.h>
#include <chrono>


int main(int argc, char * argv[])
{
    const int m_gep = 1;
    const int m_gop = 11;
    const int delta = 12;
	namespace fs = boost::filesystem; 
	if(argc != 2){
		std::cout<<" You need to give the application a directory with sample alignments"<<std::endl;
	}
	fs::path targetDir(argv[1]);
    Sequence s;
    std::cout<<"empty sequence length = "<<s.length()<<std::endl;

    ScoreMatrix distance;
    int count = 0;
    InputReader ir(targetDir.string());
    std::clock_t begin = std::clock();
    while(ir.hasNext()){

            ir.readFASTAfile();
            //std::cout<<"nucleotide = "<<ir.get_seq()<<std::endl;
            //code
            Translator t;
            Sequence tr_seq = Sequence(ir.get_seq());
            t.translate_shift(tr_seq);
            std::vector<Sequence> sequences = t.get_out_sequences();
            Sequence seq1(sequences[1]);
            Sequence seq2(ir.get_ref_seq());

            Alignment al(seq1, seq2, sequences, m_gop, m_gep, delta);
            std::string aligned_compare = ir.get_aligned_seq();
            al.compute_all_dp_matrices(0);
            std::string aligned = al.get_aligned_seq();
            assert(0);

            if (!(aligned == aligned_compare)) {
                //std::cout << " result : " << std::endl;
                //std::cout << aligned << std::endl;
                //std::cout << al.get_aligned_ref_seq() << std::endl;
                //std::cout << "score = " << al.get_score() << std::endl;
                std::vector<int> frames = al.get_v_frame();
                /*for (int i = frames.size() - 1; i >= 0; --i) {
                    std::cout << frames[i] + 1;

                }*/

                //std::cout << std::endl;

                //std::cout << " reference alignment : " << std::endl;
                //std::cout << aligned_compare << std::endl;
                //std::cout << ir.get_aligned_ref_seq() << std::endl;
                //std::cout << "score = " << ir.get_score() << std::endl;
                //std::cout << "frames = " << ir.get_frames() << std::endl;


            }

            //al.print_bt_matrix(0);
            //t.print_translated_sequences();

            //assert(ir.get_score() <= al.get_score());
            // do something with p

            //}
            //count++;
    }
    std::clock_t end = std::clock();
    std::clock_t time = (double) (end - begin)/CLOCKS_PER_SEC;
    std::cout<<"time = "<< time<< std::endl;
    std::cout<<"Finished"<<std::endl;



	
	//ir.print_input();
	/*al.print_dp_matrix(0);
	al.print_p_matrix(0);
	al.print_q_matrix(0);
	al.print_bt_matrix(0);*/
	//al.back_trace(0);

}