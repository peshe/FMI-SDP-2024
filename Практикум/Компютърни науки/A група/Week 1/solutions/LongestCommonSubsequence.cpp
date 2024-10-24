#include <iostream>

std::string LCS(const std::string& s1, const std::string& s2, int index1, int index2) {//This solution craetes a lot of copies of strings which can be slow if the input is large
    if (index1 == s1.length() || index2 == s2.length())
        return "";

    if (s1[index1] == s2[index2]) {
        return s1[index1] + LCS(s1, s2, index1 + 1, index2 + 1);
    }

    std::string res1 = LCS(s1, s2, index1 + 1, index2);
    std::string res2 = LCS(s1, s2, index1, index2 + 1);

    return (res1.length() > res2.length()) ? res1 : res2;
}



int LCSLength(const std::string& s1, const std::string& s2, size_t index1, size_t index2) {
    if (index1 >= s1.length() || index2 >= s2.length())
        return 0;

    if (s1[index1] == s2[index2]) {
        return 1 + LCSLength(s1, s2, index1+1, index2+1);
    }
    
    return std::max(LCSLength(s1, s2, index1+1, index2), LCSLength(s1, s2, index1, index2+1));
}

int main(){
    std::string a = LCS("ABCDGH","AEDFHR",0,0);
    std::cout<< a<<" " << a.length()<<std::endl;
}