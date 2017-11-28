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
    double io_time = 0.0;
    double compute_matrices_time = 0.0;
    double back_trace_time = 0.0;
    double translate_time = 0.0;
    double alignment_init_time = 0.0;


    while(ir.hasNext()){

            std::clock_t begin_io = std::clock();
            ir.readFASTAfile();
            std::clock_t end_io = std::clock();
            io_time += (double)(end_io - begin_io)/(double)CLOCKS_PER_SEC;
            //std::cout<<"nucleotide = "<<ir.get_seq()<<std::endl;
            //code

            std::clock_t begin_translate = std::clock();
            Translator t;
            Sequence tr_seq = Sequence(ir.get_seq());
            t.translate_shift(tr_seq);
            std::clock_t end_translate = std::clock();

            translate_time+= (double)(end_translate - begin_translate)/(double)CLOCKS_PER_SEC;
            std::vector<Sequence> & sequences = t.m_out_sequences;
            Sequence & seq1 = sequences[1];
            Sequence seq2 = Sequence(ir.reference);

            std::clock_t begin_init = std::clock();
            Alignment al(seq2, sequences, m_gop, m_gep, delta);
            std::clock_t end_init = std::clock();

            alignment_init_time+= (double)(end_init - begin_init)/(double)CLOCKS_PER_SEC;
            std::string aligned_compare = ir.get_aligned_seq();

            std::clock_t begin_matrices = std::clock();
            al.compute_all_dp_matrices(0);
            std::clock_t end_matrices = std::clock();

            compute_matrices_time+= (double)(end_matrices - begin_matrices)/(double)CLOCKS_PER_SEC;

            std::clock_t begin_backtrace = std::clock();
            al.backtraceing();
            std::clock_t end_backtrace = std::clock();
            back_trace_time+= (double)(end_backtrace - begin_backtrace)/(double)CLOCKS_PER_SEC;

            std::string aligned = al.get_aligned_seq();
            assert(0);

            if (!(aligned == aligned_compare)) {
                std::cout << " result : " << std::endl;
                std::cout << aligned << std::endl;
                std::cout << al.get_aligned_ref_seq() << std::endl;
                std::cout << "score = " << al.get_score() << std::endl;
                std::vector<int> frames = al.get_v_frame();
                for (int i = frames.size() - 1; i >= 0; --i) {
                    std::cout << frames[i] + 1;

                }
                std::cout << std::endl;

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

    std::cout<<"iotime = "<<io_time<<std::endl;
    std::cout<<"translate_time = "<<translate_time<<std::endl;
    std::cout<<"alignment_init_time = "<<alignment_init_time<<std::endl;
    std::cout<<"matrices_time = "<<compute_matrices_time<<std::endl;
    std::cout<<"backtrace_time = "<<back_trace_time<<std::endl;
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