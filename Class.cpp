#include "Header.h"
#include "Header.cpp"
#include "Convert.cpp"
int first_address = HexadecimalToDecimal("00400000");

class Lenh{
public:
    string name="";
    string opcode="";
    string func="";
    string PC = "";
    virtual string Bin(){return "00000000000000000000000000000000";}
    virtual void nhap(string s, int pc){return;}
};

class R_type : public Lenh{
public:
    string rs="", rt="", rd="", shamt="00000";

    void Set_Func(){
        string temp = "";
        if(name == "add")     temp = hexToBinary("20");
        if(name == "addu")    temp = hexToBinary("21");
        if(name == "and")     temp = hexToBinary("24");
        if(name == "jr")      temp = hexToBinary("08");
        func = temp.substr(2,6);
    }
    virtual void nhap(string s, int pc){
        //set name, rs, rt, rd
        s += ' ';
        name = "";
        int i=0;
        while(s[i] != ' ') name += s[i++];
        i++;
        if(name == "jr")
            while(s[i] != ' ') rs += s[i++];
        else{
            while(s[i] != ' ') rd += s[i++];
            i++;
            while(s[i] != ' ') rs += s[i++];
            i++;
            while(s[i] != ' ') rt += s[i++];
        }
        Set_Func();
    }
    virtual string Bin(){
        opcode = "000000";

        if(name == "jr"){
            rs = DecimalToBinary(reg[rs]);
            while(rs.size() < 5) rs = '0' + rs;

            return opcode + rs + "000000000000000" + func;
        }
        else{
            rs = DecimalToBinary(reg[rs]);
            while(rs.size() < 5) rs = '0' + rs;
            rt = DecimalToBinary(reg[rt]);
            while(rt.size() < 5) rt = '0' + rt;
            rd = DecimalToBinary(reg[rd]);
            while(rd.size() < 5) rd = '0' + rd;

            return opcode + rs + rt + rd + shamt + func;
        }
    }
};

class J_type : public Lenh{
public:
    string LABEL = "";

    virtual void nhap(string s, int pc){
        //set name, rs, rt, rd
        s += ' ';
        name = "";
        int i=0;
        while(s[i] != ' ') name += s[i++];
        i++;
        while(s[i] != ' ') LABEL += s[i++];
        return;
    }
    virtual string Bin(){
        if(name == "j")   opcode = "00" + hexToBinary("2");
        if(name == "jal") opcode = "00" + hexToBinary("3");
        string ans="";
        int Addr;
        for(int i=0; i<label.size(); ++i) //find address
            if(label[i].second == LABEL){Addr = label[i].first; break;}
        string JumpAddr = decToHexa(Addr);
        while(JumpAddr.size() < 8) JumpAddr = '0' + JumpAddr;
        JumpAddr = hexToBinary(JumpAddr);
        for(int i=4; i<JumpAddr.size()-2; ++i)
            ans += JumpAddr[i];
        return opcode + ans;
    }
};

class I_type : public Lenh{
public:
    string rs = "", rt = "", imme = "";
    virtual string Bin(){return "00000000000000000000000000000000";}
    virtual void nhap(string s, int pc){ cout << 1 ; return;}
};

class I_BA : public I_type{
public:
    string LABEL = "";
    int PC;
    virtual void nhap(string s, int pc){
        PC = pc;
        s += ' ';
        name = "";
        int i=0;
        while(s[i] != ' ') name += s[i++];
        i++;
        while(s[i] != ' ') rs += s[i++];
        i++;
        while(s[i] != ' ') rt += s[i++];
        i++;
        while(s[i] != ' ') LABEL += s[i++];
        return;
    }
    virtual string Bin(){
        if(name == "beq")   opcode = "00" + hexToBinary("4");
        if(name == "bne")   opcode = "00" + hexToBinary("5");
        string temp = "";
        int Addr;
        for(int i=0; i<label.size(); ++i) //find address of LABEL
            if(label[i].second == LABEL){Addr = label[i].first; break;}
        int BranchAddr = Addr - PC - 4;
        temp = bu2(BranchAddr);
        if(BranchAddr >= 0)
            while(temp.size() < 32) temp = '0' + temp;
        else
            while(temp.size() < 32) temp = '1' + temp;
        imme = temp.substr(14,16);

        rs = DecimalToBinary(reg[rs]);
        rt = DecimalToBinary(reg[rt]);

        while(rs.size() < 5) rs = '0' + rs;
        while(rt.size() < 5) rt = '0' + rt;

        return opcode + rs + rt + imme;
    }
};

class I_ZE : public I_type{
public:
    int immediate=0;

    virtual void nhap(string s, int pc){
        s += ' ';
        name = "";
        int i=0;
        while(s[i] != ' ') name += s[i++];
        i++;
        while(s[i] != ' ') rt += s[i++];
        i++;
        while(s[i] != ' ') rs += s[i++];
        i++;
        while(s[i] != ' ') imme += s[i++];
        return;
    }
    virtual string Bin(){
        opcode = "00" + hexToBinary("C");
        int i=0, checky = 1;
        if(imme[i] == '-'){
            i++;
            checky = -1;
        }
        while(i<imme.size())
            immediate = immediate*10 + (imme[i++] - '0');

        string temp = bu2(immediate * checky);
        while(temp.size() < 16) temp = '0' + temp;
        imme = temp;

        rs = DecimalToBinary(reg[rs]);
        rt = DecimalToBinary(reg[rt]);

        while(rs.size() < 5) rs = '0' + rs;
        while(rt.size() < 5) rt = '0' + rt;

        return opcode + rs + rt + imme;
    }
};
 class I_lui : public I_type{
 public:
     int immediate=0;

    virtual void nhap(string s, int pc){
        s += ' ';
        name = "";
        int i=0;
        while(s[i] != ' ') name += s[i++];
        i++;
        while(s[i] != ' ') rt += s[i++];
        i++;
        while(s[i] != ' ') imme += s[i++];
        return;
    }
    virtual string Bin(){
        opcode = "00" + hexToBinary("F");
        int i=0, checky = 1;
        if(imme[i] == '-'){
            i++;
            checky = -1;
        }
        while(i<imme.size())
            immediate = immediate*10 + (imme[i++] - '0');

        string temp = bu2(immediate * checky);
        while(temp.size() < 16) temp = '0' + temp;
        imme = temp;

        rs = "00000";
        rt = DecimalToBinary(reg[rt]);
        while(rt.size() < 5) rt = '0' + rt;

        return opcode + rs + rt + imme;
    }
 };
class I_SE : public I_type{
public:
    int immediate=0;

    virtual void nhap(string s, int pc){
        s += ' ';
        name = "";
        int i=0;
        while(s[i] != ' ') name += s[i++];
        i++;
        if(name == "addi" || name == "addiu"){
            while(s[i] != ' ') rt += s[i++];
            i++;
            while(s[i] != ' ') rs += s[i++];
            i++;
            while(s[i] != ' ') imme += s[i++];
        }
        else{
            while(s[i] != ' ') rt += s[i++];
            i++;
            while(s[i] != ' ') imme += s[i++];
            i++;
            while(s[i] != ' ') rs += s[i++];
        }
        return;
    }
    virtual string Bin(){
        if(name == "addi") opcode = hexToBinary("08");
        if(name == "addiu") opcode = hexToBinary("09");
        if(name == "lbu") opcode = hexToBinary("24");
        if(name == "lhu") opcode = hexToBinary("25");
        if(name == "lw") opcode = hexToBinary("23");
        if(name == "sw") opcode = hexToBinary("2B");
        opcode = opcode.substr(2,6);

        int i=0, checky = 1;
        if(imme[i] == '-'){
            i++;
            checky = -1;
        }
        while(i<imme.size())
            immediate = immediate*10 + (imme[i++] - '0');

        string temp = bu2(immediate * checky);
        if(checky == 1)
            while(temp.size() < 16) temp = '0' + temp;
        else
            while(temp.size() < 16) temp = '1' + temp;
        imme = temp;

        rs = DecimalToBinary(reg[rs]);
        rt = DecimalToBinary(reg[rt]);

        while(rs.size() < 5) rs = '0' + rs;
        while(rt.size() < 5) rt = '0' + rt;

        return opcode + rs + rt + imme;
    }
};
