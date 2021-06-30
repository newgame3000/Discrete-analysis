#include <iostream>
#include <cstring>

using namespace std;

const int TL = 257;

struct TString {
    char S[TL] = {0};
    int Capacity = 0;

    char& operator[](int i) {
        return S[i];
    }

     void Clear() {
        memset(S,0,TL);
        Capacity = 0;
    }

    void Push(char z) {
        S[Capacity] = z;
        Capacity += 1;
    }

    TString& operator = (const TString &vec) {
        memcpy(S, vec.S, vec.Capacity);
        Capacity = vec.Capacity;
        return *this;
    }

    bool operator == (const TString &a) {
        if (Capacity != a.Capacity){
            return false;
        }

        for(int i = 0; i < a.Capacity; ++i) {
            if(a.S[i] != S[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator != (const TString &a) {
        if (Capacity != a.Capacity){
            return true;
        }

        for (int i = 0; i < a.Capacity; ++i) {
            if (a.S[i] != S[i]) {
                return true;
            }
        }
        return false;
    }

     int Sizev() {
        return Capacity;
    }
};

struct TPatricia {

    int Id = -1;    
    int Nbit;
    unsigned long long Value;
    TString Pv;
    TPatricia *Left = nullptr;
    TPatricia *Right = nullptr; 

    ~TPatricia() {
        if ((Left != nullptr) && (Left->Nbit > Nbit)) {
            delete Left;
        }
        if ((Right != nullptr) && (Right->Nbit > Nbit)) {
            delete Right;
        }
    }

};

struct TPointers {
    TPatricia *Patr;
};

unsigned long long psize = 0;

int Searchnumber (TString &pv, TString &t) {
 
	int i = 0;
	while (pv[i] == t[i]) {
	 	i += 1;
	}
 
	int number = 7; 
 
	while ((pv[i] & (1 << number)) == (t[i] & (1 << number))) {
		number -= 1;
	}
 
	return 8 * i + 7 - number;
}


bool Number (TString &t, int bit) {
 
    if (bit == -1) {
		return false;
	}
	int i;
	i = bit / 8;
	bit = bit % 8;
	return t[i] & (1 << (7 - bit));
 
}

void Search(TPatricia *&p,  TString &t) {

    if (p == nullptr) {
        printf("NoSuchWord\n");
        return;
    }

    TPatricia *pred;
    TPatricia *cur;
    pred = p;
    cur = p->Left;

    while (cur->Nbit > pred->Nbit) {
        if (Number(t, cur->Nbit)) {
            pred = cur;
            cur = cur->Right;
        } else {
            pred = cur;
            cur = cur->Left;
        }
    }

    if (cur->Pv == t) {
        printf("OK: %llu\n", cur->Value);
    } else {
        printf("NoSuchWord\n");
    }
    return;
}

void Add(TPatricia *&p, unsigned long long value,  TString &t) {
    if (p == nullptr) {
        p = new TPatricia;
        p->Pv = t;
        p->Nbit = -1;
        p->Value = value;
        p->Left = p;
        p->Right = nullptr;
        psize += 1;
        printf("OK\n");
        return;
    }

    TPatricia *pred;
    TPatricia *cur;
    pred = p;
    cur = p->Left;

    while (cur->Nbit > pred->Nbit) {

        if (Number(t, cur->Nbit)) {
            pred = cur;
            cur = cur->Right;
        } else {
            pred = cur;
            cur = cur->Left;
        }
    }

    if (cur->Pv == t) {
        printf("Exist\n");
        return;
    }

    int newbit = Searchnumber(cur->Pv, t);

    if (newbit < pred->Nbit) {

        pred = p;
        cur = p->Left;

        while (newbit > cur->Nbit) {

            if(Number(t, cur->Nbit)) {
                pred = cur;
                cur = cur->Right;
            } else {
                pred = cur;
                cur = cur->Left;
            }
        }
    }

    bool bitadd = 0;
    bitadd = Number(t, newbit);

    TPatricia * node;
    node = new TPatricia;
    node->Value = value;
    node->Nbit = newbit;
    node->Pv = t;

    if (cur == pred->Right) {
        pred->Right = node;
    } else {
        pred->Left = node;
    }

    if (bitadd) {
        node->Right = node;
        node->Left = cur;
    } else {
        node->Right = cur;
        node->Left = node;
    }
    psize += 1;
    printf("OK\n");
}

void Patricia_delete(TPatricia *&p, TString &t) {

    if (p == nullptr) {
        printf("NoSuchWord\n");
        return;
    }

    TPatricia *pred;
    TPatricia *cur;
    TPatricia *pred_head;

    pred = p;
    cur = p->Left;

    while (cur->Nbit > pred->Nbit) {

        if (Number(t, cur->Nbit)) {
        	pred_head = pred;
            pred = cur;
            cur = cur->Right;
        } else {
        	pred_head = pred;
            pred = cur;
            cur = cur->Left;
        }
    }

    if (cur->Pv != t) {
        printf("NoSuchWord\n");
        return;
    }

    psize -= 1;

    if (pred->Nbit == -1) {
        cur->Left = nullptr;
        cur->Right = nullptr;
        delete cur;
        p = nullptr;
        printf("OK\n");
        return;
    }

    int h = 0;
    if (cur->Nbit == -1) {
        h = 1; 
        cur->Pv = pred->Pv;
        cur->Value = pred->Value; 
        cur = pred;
    }
    
    if (((cur->Left == cur) && (pred == cur)) || ((cur->Right == cur) && (pred == cur))) {
       pred = pred_head;
    }

    if (cur->Left == cur) {
        if (pred->Right == cur) {
            pred->Right = cur->Right;
            cur->Left = nullptr;
            cur->Right = nullptr;
            delete cur;
            printf("OK\n");
            return;
        } else {
            pred->Left = cur->Right;
            cur->Left = nullptr;
            cur->Right = nullptr;
            delete cur;
            printf("OK\n");
            return;
        }
    }

    if (cur->Right == cur) {
       if (pred->Right == cur) {
            pred->Right = cur->Left;
            cur->Left = nullptr;
            cur->Right = nullptr;
            delete cur;
            printf("OK\n");
            return;
        } else {
            pred->Left = cur->Left;
            cur->Left = nullptr;
            cur->Right = nullptr;
            delete cur;
            printf("OK\n");
            return;
        }
    }

    if (h == 1) {
        TPatricia *pred_head;
        pred_head = p;

        while ((pred_head->Left != cur) && (pred_head->Right != cur)) {

            if (Number(cur->Pv, pred_head->Nbit)) {
                pred_head = pred_head->Right;
            } else {
                pred_head = pred_head->Left;
            }
        }

        pred = cur;

        while ((pred->Left != cur) && (pred->Right != cur)) {
    
            if (Number(cur->Pv, pred->Nbit)) {
                pred = pred->Right;
            } else {
                pred = pred->Left;
            }
        }

        if (cur->Right == p) {
            if (pred_head->Right == cur) {
                pred_head->Right = cur->Left;
            } else {
                pred_head->Left = cur->Left;
            }

            if (pred->Left == cur) {
                pred->Left = cur->Right;
            } else {
                pred->Right = cur->Right;
            } 
    
        } else {

            if (pred_head->Right == cur) {
                pred_head->Right = cur->Right;
            } else {
                pred_head->Left = cur->Right;
            }

            if (pred->Left == cur) {
                pred->Left = cur->Left;
            } else {
                pred->Right = cur->Left;
            } 
        }

        cur->Left = nullptr;
        cur->Right = nullptr;
        delete cur;
        printf("OK\n");
        return;
    }

 
    TPatricia* newpred;
    newpred = pred;
      
    while ((newpred->Left != pred) && (newpred->Right != pred)) {
 
        if (Number(pred->Pv, newpred->Nbit)) {
            newpred = newpred->Right;
        } else {
            newpred = newpred->Left;
        }
 
    }
 
    if (pred->Left == cur) {
        if (newpred->Left == pred) {
            newpred->Left = cur;
        } else {
            newpred->Right = cur;
        }
 
        if (pred_head->Right == pred) {
            pred_head->Right = pred->Right;
        } else {
            pred_head->Left = pred->Right;
        }
 
    } else {
    
        if (newpred->Left == pred) {
            newpred->Left = cur;
        } else {
            newpred->Right = cur;
        }
 
        if (pred_head->Right == pred) {
            pred_head->Right = pred->Left;
        } else {
            pred_head->Left = pred->Left;
        }
    }
 
    cur->Pv = pred->Pv;
    cur->Value = pred->Value;
    pred->Left = nullptr;
    pred->Right = nullptr;
    delete pred;
    printf("OK\n");
    return;
}
 

void Numbers_Patricia(TPatricia *p, TPointers *ptr, int &index) {

    if (p == nullptr) {
        return;
    }
    p->Id = index;
    ptr[index].Patr = p;
    index += 1;

    if (p->Left->Nbit > p->Nbit) {
        Numbers_Patricia(p->Left, ptr, index);
    }

    if ((p->Right != nullptr) && (p->Right->Nbit > p->Nbit)) {
        Numbers_Patricia(p->Right, ptr, index);
    }
    
}

int main() {

    TPatricia *p = nullptr;

    TString v;

    while (scanf("%s", v.S) > 0) {

        if (v[0] == '+') {

            scanf("%s", v.S);

			for (int i = 0; i < TL; ++i) {
                if ('A' <= v[i] && v[i] <= 'Z') {
                    v[i] = v[i] - 'A' + 'a';
                }  
                if (v[i] == 0) {
                    break;
                }
                v.Capacity += 1;
            }
   
            unsigned long long value;
            scanf("%llu", &value);
            Add(p, value, v);
            v.Clear();
            continue;
        }

        if (v[0] == '-') {
            scanf("%s", v.S);
 			for (int i = 0; i < TL; ++i) {
                if ('A' <= v[i] && v[i] <= 'Z') {
                    v[i] = v[i] - 'A' + 'a';
                }    
                if (v[i] == 0) {
                    break;
                }
                v.Capacity += 1;
            }
            Patricia_delete(p, v);
            v.Clear();
            continue;
        }

        if (v[0] == '!') {
            scanf("%s", v.S);
 
            if (v[0] == 'S') {
 
                char a[TL];
                scanf("%s", a);
    
                FILE* file;
                file = fopen(a, "wb");
    
                if (file == NULL) {
                    printf("ERROR: can't create file\n");
                    continue;
                }

                fwrite(&psize, sizeof(unsigned long long), 1, file);
    
                if (psize == 0) {
                    printf("OK\n");
                    fclose(file);
                    continue;
                }

                TPointers *ptr = new TPointers[psize];
                int index = 0;
                Numbers_Patricia(p, ptr, index);
                TPatricia *add;

                for (unsigned long long i = 0; i < psize; ++i) {
                    add = ptr[i].Patr;
                    int vsize = add->Pv.Sizev();
                    fwrite(&(add->Value), sizeof(unsigned long long), 1, file);
                    fwrite(&(add->Nbit), sizeof(int), 1, file);
                    fwrite(&(vsize), sizeof(int), 1, file);
                    fwrite(ptr[i].Patr->Pv.S, sizeof(char), vsize, file);
                    fwrite(&(add->Left->Id), sizeof(int), 1, file);
                    if (add->Right != nullptr) {
                        fwrite(&(add->Right->Id), sizeof(int), 1, file);
                    }
                }    

                fclose(file);
                delete[] ptr;
                v.Clear();
                printf("OK\n");
                continue;

            } else {

                char a[TL];
                scanf("%s", a);

                FILE* file;
                file = fopen(a, "rb");

                if (file == NULL) {
                    printf("ERROR: can't create file\n");
                    continue;
                }

                fread(&psize,sizeof(unsigned long long), 1, file);

                if (psize == 0) {
                    delete p;
                    p = nullptr;
                    printf("OK\n");
                    fclose(file);
                    continue;
                }

                delete p;
                p = new TPatricia;
                TPointers *ptr = new TPointers[psize];
                ptr[0].Patr = p;

                for (unsigned long long i = 1; i < psize; ++i) {
                    ptr[i].Patr = new TPatricia; 
                }

                int vsize;
                int idLeft, idRight;

                for (unsigned long long i = 0; i < psize; ++i) {

                    fread(&ptr[i].Patr->Value, sizeof(unsigned long long), 1, file);
                    fread(&ptr[i].Patr->Nbit, sizeof(int), 1, file);
                    fread(&vsize, sizeof(int), 1, file);
                    ptr[i].Patr->Pv.Capacity = vsize;
                    fread(ptr[i].Patr->Pv.S, sizeof(char), vsize, file);
                    fread(&idLeft, sizeof(int), 1, file);
                    if (i > 0) {
                        fread(&idRight, sizeof(int), 1, file);
                    }

                    ptr[i].Patr->Left = ptr[idLeft].Patr;
                    if (i > 0) {
                        ptr[i].Patr->Right = ptr[idRight].Patr;
                    }
                }

                fclose(file);
                printf("OK\n");
                v.Clear();
                delete[] ptr;
                continue;
            }
        }

       	for (int i = 0; i < TL - 1; ++i) {
            if ('A' <= v[i] && v[i] <= 'Z') {
                v[i] = v[i] - 'A' + 'a';
            }    
            if (v[i] == 0) {
                break;
            }
            v.Capacity += 1;
        }

        if (v.Sizev() > 0) {
            Search(p, v);
            v.Clear();
        }
    }
    delete p;
}