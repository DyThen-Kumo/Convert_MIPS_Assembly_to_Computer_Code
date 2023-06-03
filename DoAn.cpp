#include "Class.cpp"    // Chứa lệnh I, J, R

string nhap_ten(string s){
    string name = "";
    for(int i=0; i<s.size() && s[i]!=' ' && s[i]!=':'; ++i)
        name += s[i];
    return name;
}
bool check_finish(string s){
    string finish = "j $ra";
    if(s.find(finish) != string::npos)
        return true;
    return false;
}
int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int address = first_address;
    vector<pair<int, Lenh*> > lenh;
    vector<Lenh*> lenh_chinh;
    while(true){
        string s;
        getline(fin,s);
        s = delete_space(s);
        if(check_finish(s)) break; //nhap "j $ra" de break

        string name = nhap_ten(s);
        if(check(s)){
            Lenh* temp = new Lenh;
            if(name == "add" || name == "addu" || name == "and" || name == "jr")
                temp = new R_type;
            else if(name == "j" || name == "jal")
                temp = new J_type;
            else{
                temp = new I_type;
                if(name == "beq" || name == "bne")
                    temp = new I_BA;
                else if(name == "andi")
                    temp = new I_ZE;
                else if(name == "lui")
                    temp = new I_lui;
                else
                    temp = new I_SE;
            }
            temp->nhap(s,address);
            lenh.push_back({address,temp});
            lenh_chinh.push_back(temp);
        }
        else
            label.push_back({address, name});

        address += 4;
    }
    for(int i=0; i<lenh_chinh.size(); ++i){
        string binary = lenh_chinh[i]->Bin();
        cout << binary << '\n';
        fout << binaryToHexa(binary) << '\n';
    }

}
