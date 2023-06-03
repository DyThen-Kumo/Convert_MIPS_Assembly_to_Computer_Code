#include "Header.h"

bool check(string s) //check xem là lệnh hay label
{
    for(int i=0; i<s.size(); ++i)
        if(s[i] == ':')
            return false;
    return true;
}

string delete_space(string s) // delete space and comment
{
    s = " " + s;
    string ans = "";
    for(int i=1; i<s.size() && s[i]!='#'; ++i){
        if(s[i] == ',' || s[i] == '(' || s[i] == ')')
            s[i] = ' ';
        if(s[i] == ' ' && s[i-1] != ' ')
            ans += s[i];
        if (s[i] == '\r' || s[i] == '\n' || s[i] == ' ')
            continue;
        ans += s[i];
    }
    //ans.erase(ans.begin());
    return ans;
}
