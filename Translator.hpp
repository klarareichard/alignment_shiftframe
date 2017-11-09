#include <unordered_map>
class Translator{

public:
	std::unordered_map<std::string, char> hash_map;

	Translator(){
		hash_map.insert({("ATT", "ATC", "ATA"));
        AMINOACIDS.put("I",codons);

        hash_map.insert({"ATT", 'I'});
        hash_map.insert({"ATC", 'I'});
        hash_map.insert({"ATA", 'I'});

        hash_map.insert({"CTT", 'L'});
        hash_map.insert({"CTC", 'L'});
        hash_map.insert({"CTA", 'L'});
        hash_map.insert({"CTG", 'L'});
        hash_map.insert({"TTA", 'L'});
        hash_map.insert({"TTG", 'L'});

        hash_map.insert({"GTT", 'V'});
        hash_map.insert({"GTC", 'V'});
        hash_map.insert({"GTA", 'V'});
        hash_map.insert({"GTG", 'V'});

        hash_map.insert({"TTT", 'F'});
        hash_map.insert({"TTC", 'F'});

        hash_map.insert({"TGT", 'C'});
        hash_map.insert({"TGC", 'C'});

        hash_map.insert({"GTC", 'A'});
        hash_map.insert({"GCC", 'A'});
        hash_map.insert({"GCA", 'A'});
        hash_map.insert({"GCG", 'A'});

        hash_map.insert({"GGT", 'G'});
        hash_map.insert({"GGC", 'G'});
        hash_map.insert({"GGA", 'G'});
        hash_map.insert({"GGG", 'G'});

        hash_map.insert({"CTT", 'P'});
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

        hash_map.insert({"TAA", '*'});
        hash_map.insert({"TAG", '*'});
        hash_map.insert({"TGA", '*'});

	}

};