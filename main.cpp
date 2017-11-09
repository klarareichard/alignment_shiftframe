#include "alignment.hpp"
#include "Matrix.hpp"
#include "ScoreMatrix.hpp"

int main(int argc, char * argv[])
{
   //code
	Sequence seq1("ATCAAGAATTCTAATGTA");
	Sequence seq2("MKIL");
	Alignment al(seq1, seq2, 1, 1, 1);
}