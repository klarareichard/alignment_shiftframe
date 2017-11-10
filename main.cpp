#include "alignment.hpp"
#include "Matrix.hpp"
#include "ScoreMatrix.hpp"
#include "MatrixReader.hpp"
#include "Translator.hpp"

int main(int argc, char * argv[])
{
   //code
	Translator t;
	//std::vector<Sequence> sequences(3, Sequence(""));
	Sequence tr_seq = Sequence("GAGCGGCCGTAAGAATCGGACTCTGTTGTTTGGACTTTGTCGTGTGAGCATAAATAATCGTATTTACTACACTGACGCATGTATATCCTACCAGCAGTTCACCTTGTTAATTCGGCCCTCTATTAGATGGTGGAAGGTAGTTATGTTATAATAACGAGAAACGGTTATTGCGAGTGAGAAGGTTCTTTGGAGGAAATCAACTTCTACTTAGTGATACCAATACGGTGTAGTCGCGACGTCGCAGGCTCCGCAAAAGTTGTACTTGATTTCCTCCTGAGAAAA");

	t.translate_shift(tr_seq);
	std::vector<Sequence> sequences = t.get_out_sequences();
	Sequence seq1 = sequences[0];
	std::cout<<"seq1 = "<<seq1.get_string()<<std::endl;
	Sequence seq2("SGLRMDSVSHSVSRDNISITLTRKEFQLLWLLASRAGEIIPRTVIASEIWGINFDSDTNTVDVAIRRLRAKVDDPFPEKLIATIRGMGYSFVAVKK");
	//Sequence sq2 ("ERP*ESDSVVWTLSCEHK*SYLLH*RMYILPAVHLVNSALY*MVEGSYVIITRNGYCE*EGSLEEINFYLVIPIRCSRDVAGSAKVVLDFLLRK")
	Alignment al(seq1, seq2, sequences, 1, 1, 1);
	//al.compute_smith_waterman_matrices(0);
	al.compute_all_dp_matrices();
	/*al.print_dp_matrix(0);
	al.print_p_matrix(0);
	al.print_q_matrix(0);
	al.print_bt_matrix(0);*/
	//al.back_trace(0);

}