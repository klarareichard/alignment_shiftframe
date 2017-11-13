#include "alignment.hpp"
#include "Matrix.hpp"
#include "ScoreMatrix.hpp"
#include "MatrixReader.hpp"
#include "Translator.hpp"
#include "InputReader.hpp"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp> 


int main(int argc, char * argv[])
{
	namespace fs = boost::filesystem; 
	if(argc != 1){
		std::cout<<" You need to give the application a directory with sample alignments"<<std::endl;
	}
	fs::path targetDir(argv[1]);
	fs::directory_iterator it(targetDir), eod;
	BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod))   
	{ 
	    if(fs::is_regular_file(p))
	    {
	    	InputReader ir;
			ir.readFASTAfile(p.string());
		   //code
			Translator t;
			//std::vector<Sequence> sequences(3, Sequence(""));
			Sequence tr_seq = Sequence(ir.get_seq());
			//std::cout<<"tr_seq = "<< tr_seq.get_string()<<std::endl;
			t.translate_shift(tr_seq);
			std::vector<Sequence> sequences = t.get_out_sequences();
			Sequence seq1(ir.get_seq());
			Sequence seq2(ir.get_ref_seq());
			//std::cout<<"seq1 = "<<seq1.get_string()<<std::endl;
			//Sequence seq2("SGLRMDSVSHSVSRDNISITLTRKEFQLLWLLASRAGEIIPRTVIASEIWGINFDSDTNTVDVAIRRLRAKVDDPFPEKLIATIRGMGYSFVAVKK");
			//Sequence sq2 ("ERP*ESDSVVWTLSCEHK*SYLLH*RMYILPAVHLVNSALY*MVEGSYVIITRNGYCE*EGSLEEINFYLVIPIRCSRDVAGSAKVVLDFLLRK")
			Alignment al(seq1, seq2, sequences, 1, 1, 1);
			std::string aligned_compare = ir.get_aligned_seq();
			al.compute_smith_waterman_matrices(0);
			//al.compute_all_dp_matrices();
			std::string aligned = al.get_aligned_seq();

			if(!aligned.compare(aligned_compare)){
				std::cout<<" result : "<<std::endl;
				std::cout<<aligned<<std::endl;
				std::cout<<al.get_aligned_ref_seq()<<std::endl;

				std::cout<<" reference alignment : "<<std::endl;
				std::cout<<aligned_compare<<std::endl;
				std::cout<<ir.get_aligned_ref_seq()<<std::endl;


			}

			std::cout<<" result : "<<std::endl;
			std::cout<<aligned<<std::endl;
			std::cout<<al.get_aligned_ref_seq()<<std::endl;

			std::cout<<" reference alignment : "<<std::endl;
			std::cout<<aligned_compare<<std::endl;
			std::cout<<ir.get_aligned_ref_seq()<<std::endl;

	        // do something with p
	    } 
	}

	
	//ir.print_input();
	/*al.print_dp_matrix(0);
	al.print_p_matrix(0);
	al.print_q_matrix(0);
	al.print_bt_matrix(0);*/
	//al.back_trace(0);

}