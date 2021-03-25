#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#define PI 3.14159265

#include <vector>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
#include <cstddef>

#include "structs.hpp"

using namespace std;

bool separet(vector<data>& m, short type, string num, bool isd){
    data tmp;
    if(!isd){
        stringstream number(num);
        number>>tmp.number;
        tmp.isd=0;
    }else{
        if(num.find(',')!=string::npos){
            string d=num;
            d[num.find(',')]='.';
            num=d;
        }
        tmp.dnumber=atof(num.c_str());
        tmp.isd=1;
    }
    tmp.type=type;
    m.push_back(tmp);
    return 1;
}

bool multiplechecker(vector<data>& m){
    for(unsigned int j=0;j<m.size();j++){
        if(m[j].type==0){
            return true;
        }
    }
    return false;
}

string sctct(string in){
    while(in.find("sin")!=string::npos){
        size_t tmp=in.rfind("sin");
        string number="";
        unsigned int e=0;
        for(unsigned int i=tmp+3;i<in.length();i++){
            if(isdigit(in[i])){
                number+=in[i];
            }else if(in[i]=='.'||in[i]==','){
                number+='.';
            }else{
                e=number.length()+3;
                if(number.find('.')==string::npos){
                    number+=".00";
                }
                break;
            }
        }
        double result=atof(number.c_str());
        result=sin(result*PI/180);
        string sresult=to_string(result);
        in.erase(tmp,e);
        in.insert(tmp,sresult);
    }
    while(in.find("cos")!=string::npos){
        size_t tmp=in.rfind("cos");
        string number="";
        unsigned int e=0;
        for(unsigned int i=tmp+3;i<in.length();i++){
            if(isdigit(in[i])){
                number+=in[i];
            }else if(in[i]=='.'||in[i]==','){
                number+='.';
            }else{
                e=number.length()+3;
                if(number.find('.')==string::npos){
                    number+=".00";
                }
                break;
            }
        }
        double result=atof(number.c_str());
        result=cos(result*PI/180);
        string sresult=to_string(result);
        in.erase(tmp,e);
        in.insert(tmp,sresult);
    }
    while(in.find("tan")!=string::npos){
        size_t tmp=in.rfind("tan");
        string number="";
        unsigned int e=0;
        for(unsigned int i=tmp+3;i<in.length();i++){
            if(isdigit(in[i])){
                number+=in[i];
            }else if(in[i]=='.'||in[i]==','){
                number+='.';
            }else{
                e=number.length()+3;
                if(number.find('.')==string::npos){
                    int inumber;
                    stringstream ssnumber(number);
                    ssnumber>>inumber;
                    if(inumber%90==0){
                        if(inumber%180!=0){
                            return "Hiba";
                        }
                    }
                    number+=".00";
                }
                break;
            }
        }
        double result=atof(number.c_str());
        result=tan(result*PI/180);
        string sresult=to_string(result);
        in.erase(tmp,e);
        in.insert(tmp,sresult);
    }
    in=in.substr(0,in.length()-1);
    return in;
}

string power(string a,string b){
    if(a=="0"){
        return "1";
    }
    if(b=="1"){
        return a;
    }
    if(a.find(',')!=string::npos){
            string d=a;
            d[a.find(',')]='.';
            a=d;
    }
    if(b.find(',')!=string::npos){
            string d=b;
            d[b.find(',')]='.';
            b=d;
    }
    if(a.find('.')!=string::npos||b.find('.')!=string::npos){
        double da=atof(a.c_str());
        double db=atof(b.c_str());
        return to_string(pow(da,db));
    }else{
        int ia;
        stringstream sanumber(a);
        sanumber>>ia;
        int ib;
        stringstream sbnumber(b);
        sbnumber>>ib;
        return to_string(pow(ia,ib));
    }
    return "Error";
}

string exponent(string in){
    while(in.find('^')!=string::npos){
        string a="";
        int beg=0;
        int en=0;
        for(unsigned int j=in.find('^')-1;j>=0;j--){
            if(isdigit(in[j])||in[j]=='.'||in[j]=='.'||in[j]=='-'){
                a.insert(a.begin(),in[j]);
                en++;
            }else{
                beg=j+1;
                break;
            }
        }
        string b="";
        for(unsigned int j=in.find('^')+1;j<in.length();j++){

            if(isdigit(in[j])||in[j]=='.'||in[j]=='.'||in[j]=='-'){
                b+=in[j];
                en++;
            }else{
                break;
            }
        }
        in.erase(beg,en+1);
        string tmp=power(a,b);
        in.insert(beg,tmp);
    }
    return in;
}

string sqr(string in){
    while(in.find('#')!=string::npos){
        int counter=0;
        int beg=0;
        string number="";
        string number2="";
        if(isdigit(in[in.find('#')-1])){
            for(unsigned int i=in.find('#')-1;i>=0;i--){
                if(isdigit(in[i])||in[i]=='.'||in[i]==','||in[i]=='-'){
                    number.insert(number.begin(),in[i]);
                    counter++;
                }else{
                    beg=i+1;
                    break;
                }
            }
        }
        for(unsigned int i=in.find('#')+1;i<in.length();i++){
            if(isdigit(in[i])||in[i]=='.'||in[i]==','||in[i]=='-'){
                number2+=in[i];
                counter++;
            }else{
                break;
            }
        }
        if(number==""){
            number="2";
        }
        in.erase(beg,counter+1);
        if(number=="0"){
            return "Hiba";
        }
        if(number2.find('-')!=string::npos){
            return "Hiba";
        }else{
            double dtmp=atof(number.c_str());
            dtmp = 1/dtmp;
            number=to_string(dtmp);
            string tmp=power(number2,number);
            in.insert(beg,tmp);
        }

    }
    return in;
}


string calculate(string in){
    vector<data> m;
    {
        bool need;
        bool isd=false;
        string num="";
        if(in.find('.')!=string::npos||in.find(',')!=string::npos){
            isd=true;
        }
        if(in[0]=='-'){
            data tmp;
            tmp.number=0;
            tmp.isd=0;
            tmp.type=3;
            in=in.substr(1);
            m.push_back(tmp);
        }
        for(unsigned int i=0;i<in.length();i++){
            need=false;
            if(in[i]=='*'){
                need=separet(m,0,num,isd);
                num="";
            }else if(in[i]=='/'){
                need=separet(m,1,num,isd);
                num="";
            }else if(in[i]=='+'){
                need=separet(m,2,num,isd);
                num="";
            }else if(in[i]=='-'){
                need=separet(m,3,num,isd);
                num="";
            }
            if(in[i]=='='){
                need=separet(m,4,num,isd);
            }else if(i==in.length()-1){
                cout<<"Nincs egyenloseg jel a program nem tud megfeleloen mukodni"<<endl;
            }
            if(!need){
                num+=in[i];
            }
        }
    }
    {
        unsigned int i=0;
        bool reset=false;
        do{
            if(reset){
                i=0;
                reset=false;
            }
            if(m[i].type==0){
                if(m[i].isd){
                    m[i].dnumber*=m[i+1].dnumber;
                }else{
                    m[i].number*=m[i+1].number;
                }
                m[i].type=m[i+1].type;
                m.erase(m.begin()+i+1);
                reset=true;
            }else if(m[i].type==1){
                if(m[i].isd){
                    m[i].dnumber/=m[i+1].dnumber;
                }else{
                    double f=m[i].number/m[i+1].number;
                    if(f-int(f)>0){
                        m[i].number/=m[i+1].number;
                    }else{
                        for(unsigned int k=0;k<m.size();k++){
                            string s=to_string(m[k].number);
                            s+="0.00";
                            m[k].dnumber=atof(s.c_str());
                            m[k].dnumber=m[k].number;
                            m[k].isd=1;
                        }
                        m[i].dnumber/=m[i+1].dnumber;
                    }
                }
                m[i].type=m[i+1].type;
                m.erase(m.begin()+i+1);
            }else if(m[i].type==2){
                bool finded=multiplechecker(m);
                if(!finded){
                    if(m[i].isd){
                        m[i].dnumber+=m[i+1].dnumber;
                    }else{
                        m[i].number+=m[i+1].number;
                    }
                    m[i].type=m[i+1].type;
                    m.erase(m.begin()+i+1);
                    reset=true;
                }
            }else if(m[i].type==3){
                bool finded=multiplechecker(m);
                if(!finded){
                    if(m[i].isd){
                        m[i].dnumber-=m[i+1].dnumber;
                    }else{
                        m[i].number-=m[i+1].number;
                    }
                    m[i].type=m[i+1].type;
                    m.erase(m.begin()+i+1);
                    reset=true;
                }
            }
            i++;
        }while(m.size()!=1);
    }
    if(m[0].isd){
        return to_string(m[0].dnumber);
    }else{
        return to_string(m[0].number);
    }
    return "Hiba";
}

string bracket(string in){
    {
        do{
            vector<brackets> bpos;
            unsigned int countero=0, counterc=0;
            if(in.find('(')!=string::npos){
                if(isdigit(in[in.find('(')-1])){
                    in.insert(in.find('('),"*");
                }
            }
            for(unsigned int i=0;i<in.length();i++){
                if(in[i]=='('){
                    brackets tmp;
                    tmp.id=i;
                    tmp.o=0;
                    bpos.push_back(tmp);
                    countero++;
                }else if(in[i]==')'){
                    brackets tmp;
                    tmp.id=i;
                    tmp.o=1;
                    bpos.push_back(tmp);
                    counterc++;
                }
            }
            if(counterc==countero){
                if(counterc==0){
                    in+='=';
                    if(in.find('^')!=string::npos){
                        in=exponent(in);
                    }
                    if(in.find('#')!=string::npos){
                        in=sqr(in);
                    }
                    if(in=="Hiba"){
                        return in;
                    }else{
                        return calculate(in);
                    }
                }
            }else if(counterc<countero){
                return "Tobb a nyito mint a zaro jel";
            }else if(countero<counterc){
                return "Tobb a zaro mint a nyito jel";
            }
            unsigned int open,close;
            bool opened=false;
            for(unsigned int i=0;i<bpos.size();i++){
                if(!bpos[i].o){
                    open=bpos[i].id;
                    opened=true;
                }else if(bpos[i].o&&opened){
                    close=bpos[i].id;
                    opened=false;
                }
            }
            unsigned int tmp2 = close-open;
            string tmp = in.substr(open+1,tmp2-1);
            tmp+='=';
            in.erase(open,tmp2+1);
            in.insert(open,calculate(tmp));
        }while(in.find('(')!=string::npos&&in.find(')')!=string::npos);
    }
    if(in.find('#')!=string::npos){
        in=sqr(in);
    }
    if(in.find("sin")!=string::npos||in.find("cos")!=string::npos||in.find("tan")!=string::npos||in.find("tg")!=string::npos){
        if(in.find('=')==string::npos){
            in+='=';
        }
        in=sctct(in);
    }
    if(in.find('^')!=string::npos){
        in=exponent(in);
    }
    if(in.find('+')!=string::npos||in.find('-')!=string::npos||in.find('*')!=string::npos||in.find('/')!=string::npos){
        in+='=';
        in=calculate(in);
    }
    return in;
}

string factorial(string in){
    if(in.find('!')!=string::npos){
        do{
            string number="";
            int tmp=in.find('!');
            for(unsigned int i=tmp-1;i>=0;i--){
                if(isdigit(in[i])){
                    string tmp(1,in[i]);
                    number.insert(0,tmp);
                }else if(in[i]=='.'||in[i]==','){
                    return "Csak egész számnak lehet a faktoriálisát venni";
                }
                else{
                    break;
                }
            }
            int fnum=1;
            unsigned int inumber;
            stringstream snumber(number);
            snumber>>inumber;
            for(unsigned int i=1;i<=inumber;i++){
                fnum*=i;
            }
            int num=in.find(number);
            in.erase(num,number.length()+1);
            in.insert(num,to_string(fnum));
        }while(in.find('!')!=string::npos);
    }
    string tmp=bracket(in);
    if(tmp.find('.')!=string::npos){
            unsigned int counter=0;
            for(unsigned int i=tmp.length()-1;i>tmp.find('.');i--){
                if(tmp[i]=='0'){
                    counter++;
                }else{
                    break;
                }
            }
            if(counter!=0){
                tmp.erase(tmp.find('.'),counter+1);
            }
        }
    return tmp;
}

#endif
