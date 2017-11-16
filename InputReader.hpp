#include <sstream>
#include <iostream>
#include <string>

class InputReader{
public:
	std::string read;
	std::string reference;
	std::string aligned_read;
	std::string aligned_ref;

    InputReader():read(std::string()), reference(std::string()), aligned_read(std::string()), aligned_ref(std::string()){};
	void readFASTAfile(std::string filename){

		std::string line = std::string();
		std::ifstream infile(filename);
		bool readNextTwoLines = false;
		bool readNextLine = false;
		int line_num = 0;
		
		while (std::getline(infile, line))
		{
            auto stream = std::istringstream(line);
			if(line_num == 0){
				assert(line[0] == '>');
			}else if(line_num == 1){
				stream >> read;
			}else if(line_num == 2){
				stream >> reference;
                for(int i = 0; i < reference.length(); ++i){
                    std::cout<<"input_reader"<<std::endl;
                    assert(!isspace(reference[i]));
                }
			}else if(line_num == 3){
				aligned_read = line;
			}else if(line_num == 4){
				aligned_ref = line;
			}
			line_num++;
		}

	}

	void print_input(){
		std::cout<<"reference = "<< reference <<std::endl;
		std::cout<<"read = "<< read <<std::endl;
	}

	std::string get_aligned_seq(){
		return aligned_read;
	}

	std::string get_aligned_ref_seq(){
		return aligned_ref;
	}

	std::string get_seq(){
		return read;
	}

	std::string get_ref_seq(){
		return reference;
	}
		
};