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


int main(int argc, char * argv[])
{
	namespace fs = boost::filesystem; 
	if(argc != 2){
		std::cout<<" You need to give the application a directory with sample alignments"<<std::endl;
	}
	fs::path targetDir(argv[1]);
	fs::directory_iterator it(targetDir), eod;
    Sequence s;
    std::cout<<"empty sequence length = "<<s.length()<<std::endl;

    ScoreMatrix distance;
    int count = 0;



	BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod))
	{
        if(count == 0) {
            if(fs::is_regular_file(p)) {
                InputReader ir;
                ir.readFASTAfile(p.string());
                //code
                Sequence tr_seq = Sequence(ir.get_seq());
                Sequence seq2(ir.get_ref_seq());



                Alignment_imp al_imp(tr_seq, seq2, 11, 1, 12);
                al_imp.initialize();

                al_imp.compute_matrices();

                al_imp.print_C();
                al_imp.print_D();
                al_imp.print_I();
                al_imp.print_bt();
                al_imp.print_bt_i();
                al_imp.print_bt_d();

                al_imp.back_trace();
                std::cout<<"ref seq ="<<al_imp.get_ref_seq()<<std::endl;
                std::cout<<"seq = "<<al_imp.get_seq()<<std::endl;
                std::cout<<"Nucleotide = "<<ir.get_seq()<<std::endl;
                std::cout<<"result: "<<std::endl;
                std::cout<< al_imp.get_ref_result()<<std::endl;
                std::cout<< al_imp.get_al_result()<<std::endl;
                std::cout<< "score = "<<al_imp.get_score()<<std::endl;

                std::cout<<"reference alignment:"<<std::endl;
                std::cout<<ir.get_aligned_seq()<<std::endl;
                std::cout<<ir.get_aligned_ref_seq()<<std::endl;
                std::cout<<"score = "<<ir.get_score()<<std::endl;



                //al.print_bt_matrix(0);
                //t.print_translated_sequences();

                //assert(ir.get_score() <= al.get_score());
                // do something with p


            }
            count++;
        }
	}

	
	//ir.print_input();
	/*al.print_dp_matrix(0);
	al.print_p_matrix(0);
	al.print_q_matrix(0);
	al.print_bt_matrix(0);*/
	//al.back_trace(0);

}