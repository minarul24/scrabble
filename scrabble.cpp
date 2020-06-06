/* 
   Author:    Mohammad Minarul Islam Shawon
   
   The Scrabble Game
*/

#include <iostream>
#include <set> 
#include "scrabble.hpp"



ScrabbleSolver::ScrabbleSolver()
{

}

void ScrabbleSolver::add_word( std::string const& word )
{   
    auto f1=dictionary.find(word);
    if(f1 != dictionary.end())
    {
        throw std::runtime_error("Already exists");
    }
    else
    dictionary.insert(word);
}

ScoreMap ScrabbleSolver::get_score_map()
{  
    ScoreMap result;
    int temp_score;
    for(auto word : dictionary)
    {
        temp_score = compute_score(word);
        result.insert(std::make_pair(word,temp_score));
    }
    return result;
}

ScoreMap ScrabbleSolver::find_words( TileSet const& tiles )
{
    ScoreMap rs = get_score_map();
    ScoreMap ts;
    for( auto el : rs)
    {
        if(can_make_word(el.first,tiles))
        ts.insert(el);
        
    }
    return ts;
}

ScoreMap ScrabbleSolver::find_best_words( TileSet const& tiles )
{
    ScoreMap rs;
    ScoreMap ts;
    rs=find_words(tiles);
    int score=0;
    std::string str;
    for(auto [key,value] : rs)
    {
        if(value>score)
        {
            score = value;
            str = key;
        }
            
    }
    
    for(auto [key,value] : rs)
    {
        if(value==score)
        {
            ts.insert(std::make_pair(key,score));
        }
    }
    return ts;

}

/* Static member functions */


int ScrabbleSolver::compute_score( std::string const& word )
{
    int score=0;
    for(unsigned int i=0; i<word.length(); i++)
    {
        if(word.at(i)=='a' || word.at(i)=='e' || word.at(i)=='i' || word.at(i)=='l' || word.at(i)=='n' ||word.at(i)=='o' || word.at(i)=='r' ||word.at(i)=='s' || word.at(i)=='t' || word.at(i)=='u' )
        {
            score += 1;
        }

        if( word.at(i)=='d' || word.at(i)=='g' )
        score += 2;

        if(word.at(i)=='b' || word.at(i)=='c' || word.at(i)=='m' || word.at(i)=='p')
        score += 3;

        if(word.at(i)=='f' || word.at(i)=='h' || word.at(i)=='v' || word.at(i)=='w' || word.at(i)=='y')
        score += 4;

        if(word.at(i)=='k')
        score += 5;

        if(word.at(i)=='j' || word.at(i)=='x')
        score += 8;

        if(word.at(i)=='q' || word.at(i)=='z')
        score += 10;
    }
    return score;

}

bool ScrabbleSolver::can_make_word( std::string const& word, TileSet const& tiles )
{
    std::map<char, int> M;
    for(auto ch : tiles)
    {
        if(M.find(ch) != M.end())
        {
            M[ch]++;
        }
        else
        {
            M.insert(std::make_pair(ch,1));
        }
    }//end of for each loop
    for(auto el : word)
    {
        if( M.find(el) != M.end())
        {
            if(M[el]==0)
            return false;
            
            else
            M[el]--;
        }
        else 
        return false;
    }
    return true;
}