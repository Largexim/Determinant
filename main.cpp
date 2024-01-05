#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
using namespace std;
string fileRead();
bool haveSQRT(int);
int mySQRT(int input);
string* split(const string& ,int);
long double ** makeMatrix(const string&);
int checkSize(const string&);
long double determinant_regular(long double**,int);
long double determinant_gassy_elimination(long double**,int);
void printMatrix(long double**,int);
long double** minorMatrix(long double**,int,int,int);
long double** changTwoColm(long double**,int,int,int);
//long double extra_determinant(long double**,int);
//long double** sum_of_two_matrix(long double**,int,long double**);
//long double** random_matrix(int);
long double omidRezaei(long double**,int);
long double calculateDetMinor(long double**, int, int, int);
int main() {
    int size = 0;
    string matrixData = fileRead();
    size = checkSize(matrixData);
    long double** matrix = makeMatrix(matrixData);
    while(true){
        int menu = 0;
        cout<<"1)regular way.\n2)gassy elimination way.\n3)omid rezaei far way.\n4)exit.\n";
        cin>>menu;
        if(menu==1)
            cout<<"result : "<<determinant_regular(matrix,size)<<endl;
        else if(menu==2)
            cout<<"result : "<<determinant_gassy_elimination(matrix,size)<<endl;
        else if(menu==3)
            cout<<"result : "<<omidRezaei(matrix,size)<<endl;
        else
            break;
    }
    return 0;
}
string fileRead(){
    ifstream file("/Users/largexim/Documents/C++/Determinant/matrix.txt");
    string matrixData;
    int size = 1;
    // error check
    if(!file.is_open()){
        cout<<"Error"<<endl;
        exit(1);
    }
    // read file
    {
        string temp;
        while (file >> temp) {
            if (temp != " ")
                matrixData += temp + " ";
        }
    }
    //clean string
    string temp;
    for(int i=0 ; i<matrixData.length()-1 ; i++){
        temp += matrixData[i];
    }
    matrixData = temp;

    //size check
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
long double** makeMatrix(const string& input){
    int size = 1;
    for(int i=0 ; input[i] ; i++){
        if(input[i]==' ')
            size++;
    }
    string* splited = split(input,size);

    int sqrtOfSize = mySQRT(size);
    long double** matrix = new long double * [sqrtOfSize];
    for(int i=0; i<sqrtOfSize ; i++){
        matrix[i] = new long double[sqrtOfSize];
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

long double determinant_regular(long double** array,int size){
    long double result=0;
    if(size==1)
        return array[0][0];

    for(int j=0 ; j < size ; j++){
        result += pow(-1,j) * array[0][j] * determinant_regular(minorMatrix(array,size,0,j),size-1);
    }

    return result;
}
long double** minorMatrix(long double** array,int size,int x,int y){
    long double** matrix = new long double*[size-1];
    for(int i=0;i<size-1 ;i++){
        matrix[i] = new long double [size-1];
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
    return matrix;
}

long double determinant_gassy_elimination(long double** array,int size){
    long double result=0;
    long double co = 1;
    long double** matrix = new long double*[size];
    for(int i=0 ; i<size ;i++){
        matrix[i] = new long double [size];
    }
    for(int i=0; i<size ;i++){
        for(int j=0; j<size ;j++){
            matrix[i][j]=array[i][j];
        }
    }
    for( int row=0; row<size-1 ; row++){
        for(int i=row+1 ; i < size ; i++){
            if(matrix[row][row]==0){
                bool test=false;
                for(int k=row ; k<size ; k++){
                    if(matrix[k][row]!=0){
                        changTwoColm(matrix,size,row,k);
                        co *= -1;
                        test = true;
                        break;
                    }
                }
                if(!test)
                    return 0;
            }
            long double coefficient = matrix[i][row]/matrix[row][row];
            for(int j=row ; j<size ; j++){
                matrix[i][j] -= matrix[row][j]*coefficient;
            }
        }
    }
    result = matrix[0][0];
    for(int i=1 ; i< size ; i++){
        result *= matrix[i][i];
    }
    result *= co;
    if(result==-0)
        return 0;
    return result;
}
long double** changTwoColm(long double** array,int size,int x,int y){
    for(int i=0 ; i<size ; i++){
        long double temp;
        temp = array[x][i];
        array[x][i] = array[y][i];
        array[y][i] = temp;
    }

    return array;
}

//long double extra_determinant(long double** array,int size){
//    long double result = 0;
//    long double results[1000000];
//    for(int i=0; i<1000000 ;i++){
//        results[i] = determinant_gassy_elimination(sum_of_two_matrix(random_matrix(size),size,array),size);
//    }
//    for(int i=0 ; i<1000000 ;i++){
//        result += results[i];
//    }
//    result /= 1000000;
//    return result;
//}
//long double** sum_of_two_matrix(long double** arrayA,int size,long double**arrayB){
//    long double** newMatrix = new long double*[size];
//    for(int i=0 ; i < size ; i++){
//        newMatrix[i] = new long double[size];
//    }
//    for(int i=0; i < size ; i++){
//        for(int j=0 ; j < size ; j++){
//            newMatrix[i][j] = arrayA[i][j] + arrayB[i][j];
//        }
//    }
//    return newMatrix;
//}
//long double** random_matrix(int size){
//    random_device rd;
//    mt19937 gen(rd());
//    uniform_real_distribution<> dis(-1, 1);
//    long double** randMatrix = new long double *[size];
//    for(int i=0 ; i<size; i++){
//        randMatrix[i] = new long double[size];
//    }
//    for(int i=0; i<size; i++){
//        for(int j=0; j<size; j++){
//            randMatrix[i][j] = dis(gen);
//        }
//    }
//    return randMatrix;
//}

long double omidRezaei(long double** matrix,int size){

    //printMatrix(matrix,size);

    if (size == 1)
        return matrix[0][0];

    else if (size == 2)
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);


    long double a00 = calculateDetMinor(matrix, size, 0, 0);

    long double a0n = calculateDetMinor(matrix, size, 0, size - 1);

    long double an0 = calculateDetMinor(matrix, size,size - 1, 0);

    long double ann = calculateDetMinor(matrix, size, size - 1, size - 1);

    long double** allLevelMinor = minorMatrix(matrix, size, 0, 0);

    long double a00nn = calculateDetMinor(allLevelMinor, size -1 ,size -2, size - 2);

    long double** newMatrix = new long double*[2];
    newMatrix[0] = new long double [2];
    newMatrix[1] = new long double [2];

    newMatrix[0][0] = a00;
    newMatrix[0][1] = a0n;
    newMatrix[1][0] = an0;
    newMatrix[1][1] = ann;


    long double result = 1/a00nn * omidRezaei(newMatrix, 2);
    return result;
}
long double calculateDetMinor(long double** matrix, int size, int row, int col){
    long double** minor = minorMatrix(matrix, size, row, col);

    return omidRezaei(minor, size-1);
}

void printMatrix(long double** array,int size){
    for(int i=0; i<size ; i++){
        for(int j=0; j<size ; j++){
            cout<<array[i][j]<<" ";
        }
        cout<<endl;
    }
}