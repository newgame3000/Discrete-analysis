#ifndef VECTOR_HPP
#define VECTOR_HPP
#include<iostream>

template <class T>
class TVector {
   private:
   		T *Data2;
    public:
	    int Capacity;
	    int Max;
	    T *Data;

    TVector(int n) {
	    Capacity = n;
	    Max = n * 2;
	    Data = new T[Max];
	    Data2 = 0;
    }
    TVector() {
		Capacity = 0;
	    Max = 0;
	    Data = 0;
	    Data2 = 0;
    }

   ~TVector() {
   		delete[] Data;
   		Data = 0;
	}
	
 void Push() {

	if(Data == 0) {
       Data = new T[1];
       Max = 1;
	}

	if(Capacity == Max) {
        Data2 = new T[Max * 2];
        Max = Max * 2;
	    for(int i = 0; i < Capacity; ++i) {
	       	Data2[i] = Data[i];
    	}
        delete[] Data;
        Data = Data2;
        Data2=0;  
	}

    Capacity += 1;
}

    void Nul() {
    	for(int i = 0; i < Capacity; ++i) {
    		Data[i] = T();
    	}
    }

};

#endif 