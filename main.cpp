#include "alignment.hpp"
#include "Matrix.hpp"
#include "ScoreMatrix.hpp"
#include "MatrixReader.hpp"

int main(int argc, char * argv[])
{
   //code
	Sequence seq1("SRILM");
	Sequence seq2("MKIL");
	Alignment al(seq1, seq2, 1, 1, 1);
	al.compute_smith_waterman_matrices(0);
	al.print_dp_matrix(0);
	al.print_p_matrix(0);
	al.print_q_matrix(0);
	//al.print_score_matrix();
}