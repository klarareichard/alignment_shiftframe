//
// Created by Klara Reichard on 22/11/17.
//
#include <random>
#include <iostream>
#include <unordered_set>
#include <sstream>
#include "alignment.hpp"
#include <fstream>
#include "Translator.hpp"
#include "Sequence.hpp"

enum Base{A, C, G, T};
//enum FileOutput{NucleoSeq, RefSeq, Aligned_ProtSeq, Aligned_RefSeq, Frames, Score };

class FileOutput{
    std::string nucleo_seq;
    std::string ref_seq;
    std::string aligned_protseq;
    std::string aligned_refseq;
    std::string frames;
    int score;

public:

    FileOutput(){
        aligned_protseq = "AAAA";
        aligned_refseq = "AAAA";
        frames = "1111";
        score = 1;
    };
    FileOutput(std::string nucleo_seq, std::string ref_seq, std::string aligned_protseq, std::string aligned_refseq, std::string frames, int score):
    nucleo_seq(nucleo_seq), ref_seq(ref_seq), aligned_protseq(aligned_protseq), aligned_refseq(aligned_refseq), frames(frames), score(score){}

    void set_nucleo_seq(std::string s){
        nucleo_seq = s;
    }
    void set_ref_seq(std::string s){
        ref_seq = s;
    }

    void set_aligned_protseq(std::string s){
        aligned_protseq = s;
    }

    void set_aligned_refseq(std::string s){
        aligned_refseq = s;
    }

    void set_frames(std::string s){
        frames = s;
    }

    void set_score(int s){
        score = s;
    }

    std::string get_nucleo_seq(){
        return nucleo_seq;
    }
    std::string get_ref_seq(){
        return ref_seq;
    }

    std::string get_aligned_protseq(){
        return aligned_protseq;
    }

    std::string get_aligned_refseq(){
        return aligned_refseq;
    }

    std::string get_frames(){
        return frames;
    }

    int get_score(){
        return score;
    }

};
class RandomSequenceGenerator {
public:
    typedef std::mt19937 MyRNG;
    uint32_t seed_val_length;
    MyRNG rng_length;
    std::uniform_int_distribution<uint32_t> length_dist;

    uint32_t seed_val_base;
    MyRNG rng_base;
    std::uniform_int_distribution<uint32_t> base_dist;

    RandomSequenceGenerator(int min_length, int max_length){
        length_dist = std::uniform_int_distribution<uint32_t>(min_length, max_length);
        rng_length.seed(seed_val_length);
        base_dist = std::uniform_int_distribution<uint32_t>(0,3);
        rng_base.seed(seed_val_base);
    }

    char generate_random_base(){
        int rand_base = base_dist(rng_base);
        if(rand_base == Base::A){
            return 'A';
        }else if(rand_base == Base::C){
            return 'C';
        }else if(rand_base == Base::G){
            return 'G';
        }else if(rand_base == Base::T){
            return 'T';
        }
    }
    std::string generate_random_sequence(){
        int length = length_dist(rng_length);
        std::string random_seq;
        for(int i = 1; i <= length; ++i){
            random_seq+= generate_random_base();
        }
        return random_seq;
    }
};

class RandomPositionGenerator{

public:
    double ratio;
    std::uniform_real_distribution<double> dist;
    std::mt19937 gen;
    RandomPositionGenerator(double ratio):ratio(ratio)
    {
        dist = std::uniform_real_distribution<>(0, 1);
        std::random_device rd;
        gen = std::mt19937(rd());
    }

    void delete_random(std::string &in){
        std::unordered_set<int> pos;
        for(auto it(in.begin()); it != in.end();){
            double rand = dist(gen);
            if(rand < ratio){
                it = in.erase(it);
            }else{
                ++it;
            }
        }
    }

    std::string add_random(const std::string &in){
        RandomSequenceGenerator sq(0,2);
        std::stringstream out_string;
        for(int i = 0; i < in.length(); ++i){
            double rand = dist(gen);
            if(rand < ratio){
                char rand_base = sq.generate_random_base();
                out_string << rand_base;
            }
            out_string << in[i];
        }

        std::string out_str = out_string.str();
        return out_str;
    }
};

template<typename L> void for_generated_random_seq(int num_files, int min_seq_length, int max_seq_length, double del_ratio, double ins_ratio, L handle){

    RandomSequenceGenerator rnd(min_seq_length, max_seq_length);
    RandomPositionGenerator del_r(del_ratio);
    RandomPositionGenerator add_r(ins_ratio);

    for(int i = 0; i < num_files; ++i){
        Translator t;
        FileOutput fo;
        std::string rand_seq = rnd.generate_random_sequence();
        del_r.delete_random(rand_seq);
        std::string nucleo_seq = add_r.add_random(rand_seq);
        fo.set_nucleo_seq(nucleo_seq);
        Sequence rand_seqq(rand_seq);
        t.translate(rand_seqq);
        std::string ref_seq = t.get_out_sequences()[0].get_string();
        fo.set_ref_seq(ref_seq);
        handle(fo);

    }

}

void write_random_samples_to_file(const std::string &outfile_name){
    std::ofstream outfile;
    outfile.open(outfile_name, std::ofstream::out | std::ofstream::trunc);
    if(outfile.is_open()){
        for_generated_random_seq(1000, 100, 1500, 0.05, 0.05,[&](FileOutput f){
            outfile << ">" <<std::endl;
            outfile << f.get_nucleo_seq() <<std::endl;
            outfile << f.get_ref_seq() << std::endl;
            //outfile << f.get_aligned_protseq() << std::endl;
            //outfile << f.get_aligned_refseq() << std::endl;
            //outfile << f.get_frames() << std::endl;
            //outfile << f.get_score() << std::endl;
            outfile << std::endl;
        });
    }
}



int main(int argc, char * argv[])
{
    write_random_samples_to_file("generated_sample_sequences.txt");



    return 0;
}