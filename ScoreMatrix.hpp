#pragma once 
#include <unordered_map>
#include <utility>
#include "MatrixReader.hpp"
#include <iostream>
#include "assert.h"

class ScoreMatrix{
public:
	std::unordered_map< std::string, int > hash_map;
	std::string file_name;
	
	ScoreMatrix(){
        readBlosum62("/home/klara/alignment_shiftframe/Blosum62.txt");
	}

	int getDistance(char a1, char a2){

		std::string concat = std::string();
		concat+= a1;
		concat+= a2;
        for(int i = 0; i < concat.length(); ++i){
            assert(!isspace(concat[i]));
        }
		//std::cout<<"concat = "<< concat <<std::endl;
		int distance;
		if(hash_map.find(concat) != hash_map.end()){
			distance = (hash_map.find(concat))->second;
		}else{
            std::cout<<"concat = "<<concat<<std::endl;
			distance = -1;
            assert(0);
		}
		return distance;
	}

	void print(){
		for(auto it(hash_map.begin()); it != hash_map.end(); ++it){
			std::cout<<"key = "<< it->first<<std::endl;
			std::cout<<"value = "<< it->second<<std::endl;
		}
	}

	void readBlosum62(std::string filename){
		std::string rows_and_columns;

        //std::cout<<"readBlusm"<<std::endl;
		std::string line;
		std::ifstream infile(filename);
        if(!infile.is_open()){
            std::cout<<"File not open!"<<std::endl;
        }
		int line_num = -1;
		while (std::getline(infile, line))
		{
		    std::istringstream iss(line);
            //std::cout<<"line = "<<line<<std::endl;
		    iss>>std::ws;
		    char c;
		    if(line[0] != '#'){
		    	if(line_num == -1){
			    	while(iss.get(c)){
			    		if((!isspace(c))){
			    			//std::cout<< "c = "<< c <<std::endl;
			    			rows_and_columns += c;
			    		}
			    	}
			    }else if(line[0] != '#'){
			    	int col_num = 0;
			    	iss.get(c);
			    	char row_nuc = c;
			    	int i;
			    	while(iss >> i){
			    		//if((!isspace(c))){
				    		std::string s = std::string();
				    		s += row_nuc;
				    		s += rows_and_columns[col_num];
                            for(int l = 0; l < s.length(); l ++){
                                assert(!isspace(s[l]));
                            }
				    		hash_map.insert({s, i });
				    		//std::cout<<"s = "<<s<<std::endl;
				    		//std::cout<<"distance = "<<i<<std::endl;
				    		col_num++;
				    	//}
			    	}
			    }
			    line_num++;
			}
		    // process pair (a,b)
		}

		for(int i = 0; i < rows_and_columns.length(); ++i){
			//std::cout<<" chars = "<< rows_and_columns[i]<<std::endl;
		}
	}
};