#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
 
using namespace std;
 
class TLongNumbers {
    private:
        static const int SIZEBLOCK = 4;
        static const int BASE = 10000;
        vector<int64_t> BigNumber;
 
        void DeleteZeros() {
            while (BigNumber.size() > 1 && BigNumber[BigNumber.size() - 1] == 0) {
                BigNumber.pop_back();
            }
        }
 
    public:
 
        TLongNumbers () {}
 
        TLongNumbers (const TLongNumbers & a) {
            BigNumber = a.BigNumber;
        }
 
        bool Null() {
            if (BigNumber.size() == 1 && BigNumber[0] == 0) {
                return true;
            } else {
                return false;
            }
        }
 
        friend istream & operator >> (istream & in, TLongNumbers & num) {
            string s;
            in >> s;
            num.BigNumber.clear();
            int max = s.size() / TLongNumbers::SIZEBLOCK;
            num.BigNumber.resize(max);
            for (int i = 0; i < max; ++i) {
                num.BigNumber[i] = stoi(s.substr(s.size() - (i + 1) * TLongNumbers::SIZEBLOCK, TLongNumbers::SIZEBLOCK));
            }
            if (s.size() % TLongNumbers::SIZEBLOCK != 0) {
                num.BigNumber.push_back(stoi(s.substr(0, s.size() % TLongNumbers::SIZEBLOCK)));
            } 
            num.DeleteZeros();
            return in;
        }
 
        friend ostream & operator << (ostream & out, const TLongNumbers & num) {
            out << num.BigNumber[num.BigNumber.size() - 1];
            for (int i = num.BigNumber.size() - 2; i >= 0; --i) {
                out << setfill('0') << setw(TLongNumbers::SIZEBLOCK) << num.BigNumber[i];
            }
            return out;
        }
 
        friend TLongNumbers operator + (const TLongNumbers &a, const TLongNumbers &b) {
            TLongNumbers result;
            (result.BigNumber).resize(max(b.BigNumber.size(), a.BigNumber.size()));
            int64_t newSum = 0;
            for (long unsigned int i = 0; i < max(b.BigNumber.size(), a.BigNumber.size()); ++i) {
                if (a.BigNumber.size() > i) {
                    result.BigNumber[i] += a.BigNumber[i];
                } 
                if (b.BigNumber.size() > i) { 
                    result.BigNumber[i] += b.BigNumber[i];
                }
                if (newSum != 0) {
                    result.BigNumber[i] += newSum;
                }
                newSum = result.BigNumber[i] / TLongNumbers::BASE;
                if (newSum != 0) {
                    result.BigNumber[i] -= TLongNumbers::BASE;
                }
            }
            if (newSum != 0) {
                result.BigNumber.push_back(newSum);
            }
            return result;
        }  
 
        friend TLongNumbers operator - (const TLongNumbers &a, const TLongNumbers &b) {
            int64_t newDiffer = 0;
            TLongNumbers result;
            (result.BigNumber).resize(a.BigNumber.size());
            for (long unsigned int i = 0; i < a.BigNumber.size(); ++i) {
                result.BigNumber[i] = a.BigNumber[i];
                if (newDiffer == 1) {
                    newDiffer = 0; 
                    if (result.BigNumber[i] < 1) {
                        newDiffer = 1;
                        result.BigNumber[i] = result.BigNumber[i] + TLongNumbers::BASE;
                    }
                    result.BigNumber[i] -= 1;
                }
                if (b.BigNumber.size() > i) {
                    if (result.BigNumber[i] < b.BigNumber[i]) {
                        newDiffer = 1;
                        result.BigNumber[i] += TLongNumbers::BASE;
                    }
                    result.BigNumber[i] -= b.BigNumber[i];
                }
            }
            result.DeleteZeros();
            return result;
        }
 
        friend bool operator > (const TLongNumbers &a, const TLongNumbers &b) {
            if (a.BigNumber.size() != b.BigNumber.size()) {
                return a.BigNumber.size() > b.BigNumber.size();
            }
            for (int i = a.BigNumber.size() - 1; i >= 0; --i) {
                if (a.BigNumber[i] != b.BigNumber[i]) { 
                    return a.BigNumber[i] > b.BigNumber[i];
                }
            }
            return false;
        } 
 
        friend bool operator < (const TLongNumbers &a, const TLongNumbers &b) {
            if (a.BigNumber.size() != b.BigNumber.size()) {
                return a.BigNumber.size() < b.BigNumber.size();
            }
            for (int i = a.BigNumber.size() - 1; i >= 0; --i) {
                if (a.BigNumber[i] != b.BigNumber[i]) {
                    return a.BigNumber[i] < b.BigNumber[i];
                }
            }
            return false;
        }
 
        friend bool operator == (const TLongNumbers &a, const TLongNumbers &b) {
            if (a.BigNumber.size() != b.BigNumber.size()) {
                return false;
            }
            for (int i = a.BigNumber.size() - 1; i >= 0; --i) {
               if (a.BigNumber[i] != b.BigNumber[i]) {
                   return false;
               }
            }
            return true;
        }
 
        friend TLongNumbers operator * (const TLongNumbers &a, const TLongNumbers &b) {
            TLongNumbers result;
            result.BigNumber.resize(a.BigNumber.size() + b.BigNumber.size());
            for (long unsigned int i = 0; i < a.BigNumber.size(); ++i) {
                for (long unsigned int j = 0; j < b.BigNumber.size(); ++j) {
                    result.BigNumber[i + j] += a.BigNumber[i] * b.BigNumber[j]; 
                }
            }
            for (long unsigned int i = 0; i < result.BigNumber.size() - 1; ++i) {
                result.BigNumber[i + 1] = result.BigNumber[i + 1] + result.BigNumber[i] / TLongNumbers::BASE;
                result.BigNumber[i] = result.BigNumber[i] % TLongNumbers::BASE;
            }
            result.DeleteZeros();
            return result;
        }
 
        TLongNumbers& operator = (const TLongNumbers &a) {
            if (this == &a) {
               return *this;
            }
            BigNumber = a.BigNumber;
            return *this;
        }
 
        friend TLongNumbers operator ^ (const TLongNumbers &a, TLongNumbers b) {
            TLongNumbers two;
            TLongNumbers skip;
            skip.BigNumber.push_back(1);
            two.BigNumber.push_back(2);
            if (b.Null()) {
               return skip; 
            }
            TLongNumbers result;
            result = a;
            while (b.BigNumber.size() > 1 || b.BigNumber[0] > 0) {
                if (b.BigNumber[0] & 1) {
                    skip = skip * result;
                }
                b = b / two;
                result = result * result;
            }
            return skip;
        }
        friend TLongNumbers operator / (const TLongNumbers &a, const TLongNumbers &b) {
            TLongNumbers result;
 
            TLongNumbers cur;
            if (b > a) {
                result.BigNumber.push_back(0);
                return result; 
            }
 
            cur.BigNumber.reserve(b.BigNumber.size() - 1);
 
            for (long unsigned int i = a.BigNumber.size() - b.BigNumber.size() + 1; i < a.BigNumber.size(); ++i) {
                cur.BigNumber.push_back(a.BigNumber[i]);
            }
 
            for (int i = a.BigNumber.size() - b.BigNumber.size(); i >= 0; --i) {
                cur.BigNumber.insert(cur.BigNumber.begin(), a.BigNumber[i]);
                cur.DeleteZeros();
 
                int l = 0;
                int r = TLongNumbers::BASE;
                TLongNumbers m;
 
                if (cur < b) {
                    result.BigNumber.push_back(0);
                    continue;
                }
 
                while (r - l > 1) {
                    m.BigNumber.push_back((r + l) / 2);
                    if (m * b > cur) {
                        r = m.BigNumber[0];
                    } else {
                        l = m.BigNumber[0];
                    }
                    m.BigNumber.pop_back();
                }
 
                result.BigNumber.push_back(l);
                m.BigNumber.push_back(l);          
                cur = cur - (b * m);
                cur.DeleteZeros();      
                m.BigNumber.pop_back();
            }
            reverse(result.BigNumber.begin(), result.BigNumber.end());
            result.DeleteZeros();
            return result;
        }
};