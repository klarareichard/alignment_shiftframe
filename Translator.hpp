#pragma once 
#include "Sequence.hpp"
#include <unordered_map>
#include <iostream>
#include <math.h>
class Translator{

public:
	std::unordered_map<std::string, char> hash_map;
        std::vector<Sequence>  m_out_sequences;

	Translator(){

                hash_map.insert({"ATT", 'I'});
                hash_map.insert({"ATC", 'I'});
                hash_map.insert({"ATA", 'I'});
                hash_map.insert({"CTT", 'L'});
                hash_map.insert({"CTC", 'L'});
                hash_map.insert({"CTA", 'L'});
                hash_map.insert({"CTG", 'L'});
                hash_map.insert({"TTA", 'L'});
                hash_map.insert({"TTG", 'L'});
                hash_map.insert({"ATG", 'M'});
                hash_map.insert({"GTT", 'V'});
                hash_map.insert({"GTC", 'V'});
                hash_map.insert({"GTA", 'V'});
                hash_map.insert({"GTG", 'V'});
                hash_map.insert({"TTT", 'F'});
                hash_map.insert({"TTC", 'F'});
                hash_map.insert({"TGT", 'C'});
                hash_map.insert({"TGC", 'C'});
                hash_map.insert({"GCT", 'A'});
                hash_map.insert({"GCC", 'A'});
                hash_map.insert({"GCA", 'A'});
                hash_map.insert({"GCG", 'A'});
                hash_map.insert({"GGT", 'G'});
                hash_map.insert({"GGC", 'G'});
                hash_map.insert({"GGA", 'G'});
                hash_map.insert({"GGG", 'G'});
                hash_map.insert({"CCT", 'P'});
                hash_map.insert({"CCC", 'P'});
                hash_map.insert({"CCA", 'P'});
                hash_map.insert({"CCG", 'P'});
                hash_map.insert({"ACT", 'T'});
                hash_map.insert({"ACC", 'T'});
                hash_map.insert({"ACA", 'T'});
                hash_map.insert({"ACG", 'T'});
                hash_map.insert({"TCT", 'S'});
                hash_map.insert({"TCC", 'S'});
                hash_map.insert({"TCA", 'S'});
                hash_map.insert({"TCG", 'S'});
                hash_map.insert({"AGT", 'S'});
                hash_map.insert({"AGC", 'S'});
                hash_map.insert({"TAT", 'Y'});
                hash_map.insert({"TAC", 'Y'});
                hash_map.insert({"TGG", 'W'});
                hash_map.insert({"CAA", 'Q'});
                hash_map.insert({"CAG", 'Q'});
                hash_map.insert({"AAT", 'N'});
                hash_map.insert({"AAC", 'N'});
                hash_map.insert({"CAT", 'H'});
                hash_map.insert({"CAC", 'H'});
                hash_map.insert({"GAA", 'E'});
                hash_map.insert({"GAG", 'E'});
                hash_map.insert({"GAT", 'D'});
                hash_map.insert({"GAC", 'D'});
                hash_map.insert({"AAA", 'K'});
                hash_map.insert({"AAG", 'K'});
                hash_map.insert({"CGT", 'R'});
                hash_map.insert({"CGC", 'R'});
                hash_map.insert({"CGA", 'R'});
                hash_map.insert({"CGG", 'R'});
                hash_map.insert({"AGA", 'R'});
                hash_map.insert({"AGG", 'R'});
                hash_map.insert({"TAA", 'X'});
                hash_map.insert({"TAG", 'X'});
                hash_map.insert({"TGA", 'X'});

	}

        void translate(Sequence & in_seq){
            //std::cout<<"Nucleotide sequence = "<< in_seq.get_string() << std::endl;
            Sequence out_seq;
            for(int i = 0; i < floor((double)(in_seq.length()/(double)3.0)); ++i){
                    Sequence seed = in_seq.substr(i*3, 3);
                    if(hash_map.find(seed.get_string()) != hash_map.end()){
                            char trans_char = (hash_map.find(seed.get_string()))->second;
                            out_seq.append(trans_char);
                    }else{
                            /*std::cout<<" Could not match :"<<std::endl;
                            seed.print("seed");
                            std::cout<<"seed finished"<<std::endl;
                            in_seq.print("in_seq");*/
                    }
            }
            for(int i = 0; i < out_seq.length(); ++i){
                assert(!isspace(out_seq.get_entry(i)));
            }
            m_out_sequences.push_back(out_seq);

        }

        char translate(const std::string &s){
            char trans_char;
            assert(s.length() ==3);
            if(hash_map.find(s) != hash_map.end()){
                trans_char = hash_map.find(s)->second;
            }else{
                assert(0);
                return trans_char;
            }
            return trans_char;
        }

        void translate_shift(Sequence & in_seq){
                Sequence out;
                for(int i = 0; i < 3; ++i){
                        out = in_seq.shift(i);
                        translate(out);
                }
        }

        std::vector<Sequence> get_out_sequences(){
                return m_out_sequences;
        }

        void print_translated_sequences(){
            for(int i = 0; i < 3; ++i){
                std::string out = m_out_sequences[i].get_string();
                std::cout<<"translated frame "<< i << " = "<< out <<std::endl;
            }
        }

};