#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
string fileRead();
bool haveSQRT(int);
int mySQRT(int input);
string* split(const string& ,int);
float** makeMatrix(const string&);
int checkSize(const string&);
float determinant_regular(float**,int);
float determinant_gassy_elimination(float**,int);
float** minorMatrix(float**,int,int,int);
int main() {
    int size = 0;
    size = checkSize(fileRead());
    float** matrix = makeMatrix(fileRead());
    //cout<<determinant_regular(matrix,size);
    determinant_gassy_elimination(matrix,size);
    return 0;
}
string fileRead(){
    ifstream file("/Users/largexim/Documents/C++/Determinant/matrix.txt");
    string matrixData;
    int size = 1;

    if(!file.is_open()){
        cout<<"Error"<<endl;
        exit(1);
    }

    getline(file,matrixData);


    for(int i=0 ; matrixData[i] ; i++){
        if(matrixData[i]==' ')
            size++;
    }

    if(!haveSQRT(size)){
        cout<<"can not make a matrix with this data!"<<endl;
        exit(1);
    }

    return matrixData;
}
bool haveSQRT(int input){
    int small=1;
    int big=input/2;
    int mid = (small+big)/2;

    if(small*small==input)
        return true;
    if(big*big==input)
        return true;

    while(true){
        if(mid*mid==input)
            return true;

        else if(mid*mid>input){
            big = mid;
            mid = (small+big)/2;
        }

        else if(mid*mid<input){
            small = mid;
            mid = (small+big)/2;
        }

        if(mid==small||mid==big)
            return false;
    }
}
int mySQRT(int input){
    int small=1;
    int big=input/2;
    int mid = (small+big)/2;

    if(small*small==input)
        return small;
    if(big*big==input)
        return big;

    while(true){
        if(mid*mid==input)
            return mid;

        else if(mid*mid>input){
            big = mid;
            mid = (small+big)/2;
        }

        else if(mid*mid<input){
            small = mid;
            mid = (small+big)/2;
        }
    }
}
float** makeMatrix(const string& input){
    int size = 1;
    for(int i=0 ; input[i] ; i++){
        if(input[i]==' ')
            size++;
    }

    string* splited = split(input,size);

    int sqrtOfSize = mySQRT(size);
    float** matrix = new float * [sqrtOfSize];
    for(int i=0; i<sqrtOfSize ; i++){
        matrix[i] = new float[sqrtOfSize];
    }

    int z=0;
    for(int i=0; i<sqrtOfSize; i++){
        for(int j=0 ; j<sqrtOfSize ; j++){
            matrix[i][j] = stof(splited[z]);
            z++;
        }
    }

    return matrix;
}
string* split(const string& input,int size){
    string* splited = new string[size];
    for(int i=0 , j=0; i<input.length() ; i++){
        if(input[i]!=' '){
            splited[j] += input[i];
        }
        else
            j++;
    }
    return splited;
}
int checkSize(const string& input){
    int size = 1;
    for(int i=0 ; input[i] ; i++){
        if(input[i]==' ')
            size++;
    }
    size = mySQRT(size);
    return size;
}
float determinant_regular(float** array,int size){
    float result=0;
    if(size==1)
        return array[0][0];

    for(int j=0 ; j < size ; j++){
        result += pow(-1,j) * array[0][j] * determinant_regular(minorMatrix(array,size,0,j),size-1);
    }

    return result;
}
float** minorMatrix(float** array,int size,int x,int y){
    float** matrix = new float*[size-1];
    for(int i=0;i<size-1 ;i++){
        matrix[i] = new float [size-1];
    }
    for(int inputI=0 ,matrixI=0 ; inputI< size ;inputI++){
        if(inputI!=x) {
            for (int inputJ = 0, matrixJ=0; inputJ < size; inputJ++) {
                if(inputJ!=y){
                    matrix[matrixI][matrixJ] = array[inputI][inputJ];
                    matrixJ++;
                }
            }
            matrixI++;
        }
    }
//    for(int i=0 ; i<size-1 ;i++){
//        for(int j=0; j<size-1 ;j++){
//            cout<<matrix[i][j]<<" ";
//        }
//        cout<<endl;
//    }
    return matrix;
}
float determinant_gassy_elimination(float** array,int size){
    float** matrix = new float*[size];
    for(int i=0 ; i<size ;i++){
        matrix[i] = new float [size];
    }
    for(int i=0; i<size ;i++){
        for(int j=0; j<size ;j++){
            matrix[i][j]=array[i][j];
        }
    }
    for(int i=0; i<size ;i++){
        for(int j=0; j<size ;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    for( int row=0; row<size-1 ; row++){
        for(int i=row+1 ; i < size ; i++){
            float coefficient = matrix[i][row]/matrix[row][row];
            for(int j=row ; j<size ; j++){
                matrix[i][j] -= matrix[row][j]*coefficient;
            }
        }
    }

    for(int i=0; i<size ;i++){
        for(int j=0; j<size ;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }

}