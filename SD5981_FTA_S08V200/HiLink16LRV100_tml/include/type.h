/* 
 * File:   type.h
 * Author: cwx5329785
 *
 * Created on 2020年8月25日, 下午2:27
 */

#ifndef TYPE_H
#define	TYPE_H
#include <string>
#include <vector>
using namespace std;

class ARRAY_I : public vector<int>{
    public:
        ARRAY_I(int length){
            vector_size = length;
            vector::resize(vector_size);
        }
        ARRAY_I(){
            
        }
        int init(int init_value){
            for (unsigned int i = 0;i < vector::size();i++){
                vector::at(i) = init_value;
            }
            return 0;
        }
        private:
            int vector_size;
};

class ARRAY_D : public vector<double>{
    public:
        ARRAY_D(int length){
            vector_size = length;
            vector::resize(vector_size);
        }
        ARRAY_D(){
            
        }
        int init(double init_value){
            for (unsigned int i = 0;i < vector::size();i++){
                vector::at(i) = init_value;
            }
            return 0;
        }
        ARRAY_D operator*(const double &b){
            ARRAY_D c(this->size());
            for(unsigned int i = 0;i < this->size();i++){
                c [i] =this->at(i)*b;
            }
            return c;
        }
        private:
            int vector_size;
};

typedef bool Boolean;
typedef  int INT;
typedef  long LONG;
typedef unsigned int uint;
typedef unsigned int UINT;
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef std::string STRING;
typedef double DOUBLE;
//typedef std::vector<int> ARRAY_I ;
//typedef std::vector<double> ARRAY_D;
typedef std::vector<INT> INT_VECTOR;
typedef std::vector<double> DOUBLE_VECTOR;
typedef std::vector<STRING> STRING_VECTOR;


#endif	/* TYPE_H */

