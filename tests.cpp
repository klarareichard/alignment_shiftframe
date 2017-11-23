#include <gtest/gtest.h>
#include "alignment.hpp"
#include "Translator.hpp"
#include "InputReader.hpp"
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include "alignment_global.hpp"
#include <limits>
#include "Sequence.hpp"

class AlignmentTest : public testing::TestWithParam<const char*>{
public:
    Alignment al;
    Translator t;
    ScoreMatrix distance;

    AlignmentTest(){
        namespace fs = boost::filesystem;
        std::string file_path(GetParam());

        fs::path targetDir(file_path);
        fs::directory_iterator it(targetDir), eod;
        Sequence s;
        std::cout<<"empty sequence length = "<<s.length()<<std::endl;

        ScoreMatrix distance;
        int count = 0;

        BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod)) {
            if(count == 0) {
                if (fs::is_regular_file(p)) {
                    InputReader ir;
                    ir.readFASTAfile(p.string());
                    //code
                    Translator t;
                    Sequence tr_seq = Sequence(ir.get_seq());
                    t.translate_shift(tr_seq);
                    std::vector<Sequence> sequences = t.get_out_sequences();
                    Sequence seq1(sequences[1]);
                    Sequence seq2(ir.get_ref_seq());

                    Alignment al(seq1, seq2, sequences, 11, 1, 12);
                    std::string aligned_compare = ir.get_aligned_seq();
                    al.compute_all_dp_matrices(0);

                }

                count++;
            }
        }

    }


    virtual void TearDown(){

    }
};

//INSTANTIATE_TEST_CASE_P(ScoreCheck, AlignmentTest, ::testing::Values("/Users/klara/alignment_shiftframe/Frameshift_samples"));

/*TEST_P(AlignmentTest,  ScoreCheck){
    std::string al_seq = al.get_aligned_seq();
    std::string al_ref_seq = al.get_aligned_ref_seq();
    int real_score = 0;
    for(int i = 0; i < al_seq.length(); ++i){
        real_score += distance.getDistance(al_seq[i], al_ref_seq[i]);
    }
    int score = al.get_score();
    ASSERT_EQ(real_score, score);
}*/

TEST(AlignmentGlobal, dna_gapfunction){
    int i = 6;
    Alignment_imp a(Sequence("ACGT"), Sequence("LST"), 11, 1, 12);
    int gap_6 = a.dna_gap(i);
    ASSERT_EQ(gap_6, -13);
    int gap_4 = a.dna_gap(4);
}
TEST(numeric_limits, numeric_limits){
    int infinity = -std::numeric_limits<double>::infinity();
    int test_val = -std::numeric_limits<double>::infinity()-1.0;
    ASSERT_EQ(test_val, infinity);
}

TEST(AlignmentGlobal, compute_matrices){



}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}