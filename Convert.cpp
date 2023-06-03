#include "Header.h"

string DecimalToBinary(int num)
{
    string str = "";
    while(num){
        if(num & 1)
            str += '1';
        else
            str += '0';
        num >>= 1;
    }
    for(int i=0; i<str.size()/2; ++i)
        swap(str[i],str[str.size()-1-i]);
    return str;
}

int HexadecimalToDecimal(string hexVal)
{
    int len = hexVal.size();
    int base = 1;
    int dec_val = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (hexVal[i] >= '0' && hexVal[i] <= '9') {
            dec_val += (int(hexVal[i]) - 48) * base;
            base = base * 16;
        }
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
            dec_val += (int(hexVal[i]) - 55) * base;
            base = base * 16;
        }
    }
    return dec_val;
}

string hexToBinary(string s)
{
    string ans = "";
    for(int i=0; i<s.size(); ++i){
        if(s[i] == '0')   ans += "0000";
        if(s[i] == '1')   ans += "0001";
        if(s[i] == '2')   ans += "0010";
        if(s[i] == '3')   ans += "0011";
        if(s[i] == '4')   ans += "0100";
        if(s[i] == '5')   ans += "0101";
        if(s[i] == '6')   ans += "0110";
        if(s[i] == '7')   ans += "0111";
        if(s[i] == '8')   ans += "1000";
        if(s[i] == '9')   ans += "1001";
        if(s[i] == 'A')   ans += "1010";
        if(s[i] == 'B')   ans += "1011";
        if(s[i] == 'C')   ans += "1100";
        if(s[i] == 'D')   ans += "1101";
        if(s[i] == 'E')   ans += "1110";
        if(s[i] == 'F')   ans += "1111";
    }
    return ans;
}

string decToHexa(int n)
{
    string ans = "";
    while (n != 0) {
        int rem = 0;
        char ch;
        rem = n % 16;
        if (rem < 10)
            ch = rem + 48;
        else
            ch = rem + 55;
        ans += ch;
        n = n / 16;
    }
    int i = 0, j = ans.size() - 1;
    while(i <= j)
    {
      swap(ans[i], ans[j]);
      i++;
      j--;
    }
    return ans;
}

string bu2(int x){
    string bin = DecimalToBinary(abs(x));
    if(x >= 0)
        return bin;
    else{
        bool ok = false;
        for(int i=bin.size()-1; i>=0; --i){
            if(!ok && bin[i] == '1'){ok = true; continue;} // bit 1 đầu tiên từ phải qua

            if(ok && bin[i] == '0'){bin[i] = '1'; continue;}
            if(ok && bin[i] == '1'){bin[i] = '0'; continue;}
        }
        return bin;
    }
}
string binaryToHexa(string s){
    string ans = "";
    for(int i=0; i<s.size(); i+=4){
        int temp = (s[i]-'0')*8 + (s[i+1]-'0')*4 + (s[i+2]-'0')*2 + (s[i+3]-'0')*1;
        if(temp < 10)
            ans += temp + '0';
        else
            ans += (temp-10) + 'A';
    }
    return ans;
}
