#include <iostream>

#include "src/functions.hpp"

using namespace std;

int main(){
    cout<<"Kerem adja meg a szamokat illetve a muveleteket."<<endl;
    string beker;
    getline(cin,beker);
    //cin>>beker;
    string tmp=factorial(beker);
    if(tmp=="Hiba"){
        cout<<"Hiba"<<endl;
    }else{
        cout<<beker<<"="<<tmp <<endl;
    }
    system("pause");
    return 0;
}
