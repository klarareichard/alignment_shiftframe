//
// Created by Klara Reichard on 17.01.18.
//

#include <unordered_map>
#include "Sequence.hpp"
#include <vector>

class SeedFinder{
public:
    std::string m_ref;
    std::string m_query;
    std::vector<std::pair<int, int>> seed_positions;
    std::unordered_map<std::string,  std::vector<int>> hash_map;
    SeedFinder(std::string ref, std::string query):m_ref(ref), m_query(query){
        readInHashmap();
    };

    void readInHashmap(){
        for(int i = 0; i < m_ref.length() - 2; ++i){
            std::string seed = m_ref.substr(i, 3);
            std::cout<<"seed = "<<seed<<std::endl;
            auto found_it = hash_map.find(seed);
            if(found_it != hash_map.end()){
                found_it->second.push_back(i);
            }else{
                std::vector<int> vec;
                vec.push_back(i);
                hash_map.insert({seed,vec });
            }
        }
    }

    void findSeeds(){
        for(int i = 0; i < m_query.length() - 2; ++i){
            auto found_it = hash_map.find(m_query.substr(i, 3));
            if(found_it != hash_map.end()){
                std::vector<int> ref_positions = found_it->second;
                for(int ref_index = 0; ref_index < ref_positions.size(); ++ref_index){
                    seed_positions.push_back(std::make_pair(i, ref_positions[ref_index]));
                }
            }
        }
    }

    void print_seed_positions(){
        for(int i = 0; i < seed_positions.size(); ++i){
            std::cout<<"query_pos = "<<seed_positions[i].first<<std::endl;
            std::cout<<"ref_pos = "<<seed_positions[i].second<<std::endl;
        }
    }

    void print_hash_map(){
        for(auto it(hash_map.begin()); it != hash_map.end(); ++it){
            std::cout<<"Key = "<<it->first<<std::endl;
            for(int i = 0; i < it->second.size(); ++i){
                std::cout<<"Value = "<<it->second[i]<<std::endl;
            }
        }
    }

    std::vector<std::pair<int, int>> getSeedPositions(){
        return seed_positions;
    }


};
