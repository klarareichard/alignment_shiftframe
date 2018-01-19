//
// Created by Klara Reichard on 19.01.18.
//
#include <string>
#ifndef ALIGNMENT_SHIFTFRAME_SEEDEXTENDER_H
#define ALIGNMENT_SHIFTFRAME_SEEDEXTENDER_H

#endif //ALIGNMENT_SHIFTFRAME_SEEDEXTENDER_H
class SeedExtender{
    int ref_pos;
    int query_pos;
    virtual  std::pair<std::string, std::string> getAlignment() = 0;
    virtual void setSeeds(int iref_pos, int iquery_pos){
        ref_pos = iref_pos;
        query_pos = iquery_pos;
    }
};
