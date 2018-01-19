
#include "SeedExtender.h"
#include "SeedFinder.hpp"

class SeedAndExtendAlgorithm{
    std::string query;
    std::string ref;
    SeedFinder sf;
    SeedExtender s;

public:
    SeedAndExtendAlgorithm(std::string iquery, std::string iref, SeedExtender is):query(iquery), ref(iref), sf(query, ref), s(is){};

    std::vector<std::pair<std::string, std::string>> computeAlignments(){
        sf.findSeeds();
        std::vector<std::pair<std::string, std::string>> alignments;
        std::vector<std::pair<int, int>> seeds = sf.getSeedPositions();
        for(int i = 0; i < seeds.size(); ++i){
            s.setSeeds(seeds[i].first, seeds[i].second);
            auto alignment = s.getAlignment();
            alignments.push_back(alignment);
        }
        return alignments;
    }

};