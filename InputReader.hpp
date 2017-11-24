#include <sstream>
#include <iostream>
#include <string>

class InputReader{
public:
	std::string read;
	std::string reference;
	std::string aligned_read;
	std::string aligned_ref;
    std::string frames;
    int score;

    InputReader():read(std::string()), reference(std::string()), aligned_read(std::string()), aligned_ref(std::string()){};
	void readFASTAfile(std::string filename){

		std::string line = std::string();
		std::ifstream infile(filename);
		bool readNextTwoLines = false;
		bool readNextLine = false;
		int line_num = 0;
		
		while (std::getline(infile, line))
		{
            std::istringstream iss(line);
            auto stream = std::istringstream(line);
			if(line_num == 0){
				assert(line[0] == '>');
			}else if(line_num == 1){
				stream >> read;
			}else if(line_num == 2){
				stream >> reference;
                for(int i = 0; i < reference.length(); ++i){
                    assert(!isspace(reference[i]));
                }
			}else if(line_num == 3){
				aligned_read = line;
			}else if(line_num == 4){
				aligned_ref = line;
			}else if(line_num == 5){
                iss >> frames;
            }else if(line_num == 6) {
                iss >> score;
            }
			line_num++;
		}

	}

    std::string get_frames(){
        return frames;
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

    int get_score(){
        return score;
    }
		
};