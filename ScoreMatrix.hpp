#pragma once 
#include <unordered_map>
#include <utility>
#include "MatrixReader.hpp"
#include <iostream>

class ScoreMatrix{
public:
	std::unordered_map< std::string, int > hash_map;
	std::string file_name;
	
	ScoreMatrix(){
		readBlosum62("Blosum62.txt");
	}

	int getDistance(char a1, char a2){

		std::string concat = "";
		concat+= a1;
		concat+= a2;
		std::cout<<"concat = "<< concat <<std::endl;
		int distance;
		if(hash_map.find(concat) != hash_map.end()){
			distance = (hash_map.find(concat))->second;
		}else{
			distance = -1;
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

		std::string line;
		std::ifstream infile(filename);
		int line_num = -1;
		infile>>std::ws;
		while (std::getline(infile, line))
		{
		    std::istringstream iss(line);
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
				    		std::string s = "";
				    		s += row_nuc;
				    		s += rows_and_columns[col_num];
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