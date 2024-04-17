#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        std::vector<int> nums;
        for(int i=k.size()-1; i>=0;i--){
            nums.push_back(letterDigitToNumber(k.at(i)));
        }
        unsigned long long fin[5];
        int numIdx=4;
        int sub=0;
        unsigned long long val=0;
        for(int i=0; i < nums.size(); i++)
        {
            val += nums[i] * pow(36,i-sub);
            if((i+1)%6==0){
               fin[numIdx]=val;
               val=0; 
               numIdx--;
               sub+=6;
            }
        }
        while(numIdx>=0){
            fin[numIdx]=val;
            val=0;
            numIdx--;
        }
        HASH_INDEX_T retVal=0;
        for(int i=0; i<5;i++){
            retVal+=fin[i]*rValues[i];
        }
        return retVal;


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
      if(isupper(letter)){letter = tolower(letter);}
      int num = letter - '0';
      if(num>9){return letter - 'a';}
      else{return num+26;}
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
