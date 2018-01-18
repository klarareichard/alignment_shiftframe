//
// Created by Klara Reichard on 18.01.18.
//

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
#include "SeedFinder.hpp"
#include <chrono>

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
    int count = 0;

    BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod))
    {

        std::cout<<"File = "<<p.string()<<std::endl;

        if(fs::is_regular_file(p)) {
            InputReader ir(p.string());
            ir.readFASTAfile();
            //code
            Sequence tr_seq = Sequence(ir.get_seq());
            Sequence seq2(ir.get_ref_seq());
            SeedFinder sf(tr_seq.get_string(), seq2.get_string());
            sf.findSeeds();
            std::vector<std::pair<int, int>> seed_positions = sf.getSeedPositions();

            for(int i = 0; i < seed_positions.size(); ++i){
                std::cout<<"query position = "<< seed_positions[i].first <<std::endl;
                std::cout<<"reference position = "<< seed_positions[i].second<<std::endl;
            }





        }
    }


    //ir.print_input();
    /*al.print_dp_matrix(0);
    al.print_p_matrix(0);
    al.print_q_matrix(0);
    al.print_bt_matrix(0);*/
    //al.back_trace(0);

}
