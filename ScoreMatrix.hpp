#pragma once 
#include <unordered_map>
#include <utility>

class ScoreMatrix{
public:
	std::unordered_map< std::string, int > hash_map;
	ScoreMatrix(){
		/*auto pair1 = std::make_pair('A', 'A'); 
		hash_map.insert({pair1, -1});

		pair1 = std::make_pair('A', 'C'); 
		hash_map.insert({pair1, 1});

		pair1 = std::make_pair('A', 'G'); 
		hash_map.insert({pair1, 0.5});

		pair1 = std::make_pair('A', 'T'); 
		hash_map.insert({pair1, 1});

		pair1 = std::make_pair('C', 'A'); 
		hash_map.insert({pair1, 1});

		pair1 = std::make_pair('C', 'C'); 
		hash_map.insert({pair1, -1});

		pair1 = std::make_pair('C', 'G'); 
		hash_map.insert({pair1, 1});

		pair1 = std::make_pair('C', 'T'); 
		hash_map.insert({pair1, 0.5});

		pair1 = std::make_pair('G', 'A'); 
		hash_map.insert({pair1, 0.5});

		pair1 = std::make_pair('G', 'C'); 
		hash_map.insert({pair1, 1});

		pair1 = std::make_pair('G', 'G'); 
		hash_map.insert({pair1, -1});

		pair1 = std::make_pair('G', 'T'); 
		hash_map.insert({pair1, 1});

		pair1 = std::make_pair('T', 'A'); 
		hash_map.insert({pair1, 1});

		pair1 = std::make_pair('T', 'C'); 
		hash_map.insert({pair1, 0.5});

		pair1 = std::make_pair('T', 'G'); 
		hash_map.insert({pair1, 1});

		pair1 = std::make_pair('T', 'T'); 
		hash_map.insert({pair1, -1});*/

	}

	int getDistance(char a1, char a2){

		std::string concat = "";
		concat+= a1;
		concat+= a2;
		assert(hash_map.find(concat) != hash_map.end());
		int distance = (hash_map.find(concat))->second;
		return distance;
	}
};