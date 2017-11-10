class InputReader{
public:
	std::string read;
	std::string reference;

	void readFASTAfile(std::string filename){

		std::string line;
		std::ifstream infile(filename);
		bool readNextTwoLines = false;
		bool readNextLine = false;
		int line_num = 0;
		
		while (std::getline(infile, line))
		{
			if(line_num == 0){
				assert(line[0] == '>');
			}else if(line_num == 1){
				read = line;
			}else if(line_num == 2){
				reference = line;
			}
			line_num++;
		}

	}

	void print_input(){
		std::cout<<"reference = "<< reference <<std::endl;
		std::cout<<"read = "<< read <<std::endl;
	}
		
};