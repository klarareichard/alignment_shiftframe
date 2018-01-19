#include "ScoreMatrix.hpp"
#include "SeedExtender.h
enum Direction{Left, Right};
class SeedExtender_impl: public SeedExtender{

    std::string query;
    std::string reference;
    int ref_pos;
    int query_pos;
    int current_score;
    int best_score;
    bool right_extension_finished;
    bool left_extension_finished;
    ScoreMatrix score;
    int left_shift;
    int right_shift;
    int best_left_shift;
    int best_right_shift;
    double ratioFromOpti;

public:
    SeedExtender_impl(int iref_pos, int iquery_pos):ref_pos(iref_pos), query_pos(iquery_pos), right_extension_finished(false),
                                               left_extension_finished(false), left_shift(0), right_shift(0){
        current_score = computeSeedScore();
        best_score = current_score;
        initializeShifts();
        ratioFromOpti = 0.2;

    }

    SeedExtender_impl(): right_extension_finished(false), left_extension_finished(false), left_shift(0), right_shift(0){
        current_score = computeSeedScore();
        best_score = current_score;
        initializeShifts();
        ratioFromOpti = 0.2;
    }

    void setSeedPositions(int iref_pos, int iquery_pos){
        ref_pos = iref_pos;
        query_pos = iquery_pos;
    }

    int computeSeedScore(){
        int seedScore = 0;
        for(int i = 0; i < 3; ++i){
            int distAtI = score.getDistance(query[query_pos+i], reference[ref_pos+i]);
            seedScore += distAI;
        }

        return seedScore;
    }

    void initializeShifts(){
        left_shift += 1;
        right_shift += 3;
        best_left_shift = left_shift;
        best_right_shift = right_shift;
    }

    void setExtensionFinished(Direction dir){
        if(dir == Direction::Left){
            left_extension_finished = true;
        }else{
            right_extension_finished = true;
        }
    }

    void extend(Direction dir){
        char query_char;
        char ref_char;
        if(dir == Direction::Left){
            query_pos = query_pos - left_shift;
            ref_pos = reference - left_shift;

        }else{
            query_pos = query_pos + right_shift;
            ref_pos = ref_pos + right_shift;
        }
        query_char = query[query_pos];
        ref_char = ref[ref_pos];
        int addScore = score.getDistance(query_char, ref_char);
        current_score = current_score + addScore;
        if(current_score < ((double)best_score * (double) (1. - ratioFromOpti))){
            setExtensionFinished(dir);
        }else if(current_score > best_score){
            best_score = current_score;
            best_right_shift = right_shift;
            best_left_shift = left_shift;
        }

    }

    std::pair<int, int> extend(){
        while(!right_extension_finished || !left_extension_finished){
            if(!right_extension_finished){
                extend(Direction::Right);
                right_shift++;
            }else{
                extend(Direction::Left);
                left_shift++;
            }
        }
        return std::make_pair(best_left_shift, best_right_shift);
    }

    std::pair<std::string, std::string> getAlignment(){
        std::string query_string;
        std::string ref_string;
        for(int i = -left_best_shift; i < right_best_shift; ++i){
            query_string.push_back(query[query_pos+i]);
            ref_string.push_back(reference[ref_pos+i]);
        }
        return std::make_pair<query_string, ref_string>;
    }
};