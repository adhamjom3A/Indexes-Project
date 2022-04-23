#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <map>
#include <sstream>
using namespace std;
fstream file, primaryFile,secondryFile;
fstream fileDepartment,primaryFileDepartment,secondryFileDepartment;
vector<pair<string,int>>primaryMap;
set<pair<string,set<string>>> sett;
vector<pair<string,string>> IDS;
set<string> setOfEmp;
vector<pair<string,int>>primaryMapDepartment;
set<pair<string,string>> settDepartment;
vector<pair<string,string>> IDSDepartment;
set<string> setOfDep;
struct pIndex{
    char id[13];
    int byteOfSet;
    bool operator<(const pIndex &r) const { // for the sort function
        return strcmp(id, r.id) < 0;
    }
};
class employee {
public:
    char Employee_ID[13]=" ";// primary
    char Dept_ID[30]=" ";
    char Employee_Name[50]=" ";
    char Employee_Position[50]=" ";
    friend ostream &operator<<(ostream &output, const employee &emp )
    {
        output<<"\n========employee "<<emp.Employee_ID<<" info ========\n"<<"name: "<<emp.Employee_Name<<"\ndep: "<<emp.Dept_ID<<"\nposition: "<<emp.Employee_Position<<endl;
        output<<"\n========================================================\n ";
        return output;
    }

};
void writePrimary();
int countDigit(long long n){
    int count = 0;
    while (n != 0)
    {
        n = n / 10;
        ++count;
    }
    return count;
}
void primarySort(){
    sort(primaryMap.begin(),primaryMap.end());
    writePrimary();
}
void writePrimary();
void writePrimary(){
    primaryFile.open("primaryEmployee.txt",ios::out);
    primarySort();
    for(auto &iter : primaryMap)
    {
        primaryFile<<iter.first<<'|'<<iter.second<<'\n';
    }
    primaryFile.close();
}
void readPrimary(){
    primaryMap.clear();
    primaryFile.open("primaryEmployee.txt",ios::in|ios::app);
    string ID;
    string bos;
    while(!primaryFile.eof())
    {
        pIndex pi;
        getline(primaryFile,ID,'|');
        getline(primaryFile,bos,'\n');
        if (bos==""||ID=="") break;
        else{
            pi.byteOfSet = stoi(bos);
            primaryMap.push_back({ID,pi.byteOfSet});
        }
    }
    primaryFile.close();
}
int byteoffset=0;
void addEmplyee(employee emp){
    int recSize=0;
    cout << endl << "Enter employee  ID (Max 13 Letters):";
    cin >> emp.Employee_ID;
    recSize+=strlen(emp.Employee_ID);
    cout << "Enter employee ID-Department (Max 30 Letters) :";
    cin >> emp.Dept_ID;
    recSize+= strlen(emp.Dept_ID);
    cout << "Enter employee  Name (Max 50 Letters) :";
    cin >> emp.Employee_Name;
    recSize+= strlen(emp.Employee_Name);
    cout << "Enter employee position (Max 50 Letters) :";
    cin >> emp.Employee_Position;
    recSize+= strlen(emp.Employee_Position)+7;
    file.open("dataFile.txt",ios::app);
    recSize+=countDigit(recSize);
    file<<'$'<<recSize<<'|'<<emp.Employee_ID<<'|'<<emp.Dept_ID<<'|'<<emp.Employee_Name<<'|'<<emp.Employee_Position<<'|'<<'\n';
    primaryFile.open("primaryEmployee.txt",ios::app);
    primaryFile<<emp.Employee_ID<<'|'<<byteoffset<<'\n';
    string str;
    //primaryFile.seekg(0,ios::cur);
    getline(primaryFile,str,'|');
    getline(primaryFile,str,'\n');
    if(!(str=="")) {byteoffset= stoi(str);}

    byteoffset+=(recSize);
    primaryFile.close();
    file.close();
}
int binarySearch(char id[]){
    sort(primaryMap.begin(),primaryMap.end());
    int start=0, mid, end=primaryMap.size()-1;
    // cout<<"endddd>>>"<<end<<endl;
    while(start<=end)
    {
        mid=(start+end)/2;
        if(primaryMap[mid].first<id)
        {
            start=mid+1;
        } else if(primaryMap[mid].first>id)
        {
            end=mid-1;
        }
        else if(primaryMap[mid].first==id){
            return primaryMap[mid].second;
        }
        else{ return -1;}
    }
}
employee searchByID(char id[]){

    employee e;
    int bos=binarySearch(id);
    // cout<<"byte offset = "<<bos<<endl;
    if(bos==-1)
    {cout<<"employee not found"; }
    else {
        file.open("dataFile.txt", ios::in|ios::out);
        file.unsetf(ios::skipws);
        file.seekg(bos, ios::beg);

        string str;
        getline(file,str,'|');
        getline(file,str,'|');
        strcpy(e.Employee_ID,str.c_str());
        // cout<<e.Employee_ID;
        getline(file,str,'|');
        strcpy(e.Dept_ID,str.c_str());
        getline(file,str,'|');
        strcpy(e.Employee_Name,str.c_str());
        getline(file,str,'|');
        strcpy(e.Employee_Position,str.c_str());
    }
    cout<<e;
    file.close();
    return e;
}
void primaryDeletion(char ID[]);
void dataFileDeletion(char ID[]){
    int bos =  binarySearch(ID);
    file.open("dataFile.txt", ios::in|ios::out);
    file.seekg(bos,ios::beg);
    file.put('*');
    file.close();
    cout<<"msg"<<endl;
    primaryDeletion(ID);

}
void primaryDeletion(char ID[]){
    readPrimary();

    string str;
    str=ID;
    for(int i=0;i<primaryMap.size();i++)
    {
        cout<<"ssss"<<endl;
        if(primaryMap[i].first==str)
        {
            cout<<primaryMap[i].first<<endl;
            primaryMap.erase(primaryMap.begin()+i);

        }
    }

    writePrimary();
}
void WriteSecondryFile();
void secondryStructure()
{
    file.open("dataFile.txt",ios::out|ios::in);
    int i=0;
    while(!(file.eof()))
    {
        string str,str2;
        getline(file,str,'|');
        getline(file,str,'|');
        getline(file,str2,'|');
        IDS.push_back({str2,str});
        // IDS[i].first=str2;
        //IDS[i].second=str;
        getline(file,str,'|');
        getline(file,str,'|');
        i++;
    }
    for(auto& iter:IDS)
    {
        string str=iter.first;
        for(auto &iter2:IDS)
        {
            if(iter2.first==str){
                setOfEmp.insert(iter2.second);
            }
        }
        sett.insert({str,setOfEmp});
        setOfEmp.clear();
    }
    int ii =0;
    /*for(auto&iter:sett)
    {
        if(!(iter.first.empty())){
        cout<<iter.first<<" ";
        ii++;
        for(auto&iter2:iter.second)
        {
            cout<<iter2<<" ";
        }cout<<endl;}
    }
    cout<<ii;*/
    WriteSecondryFile();
    sett.clear();
    file.close();
}
void parseEmployeeID(string s){
    setOfEmp.clear();
    string arr="";
    for (int i=0;i<s.length();i++){
        if (s[i]!='|'){
            arr+=s[i];
        }
        else if (s[i]=='|') {
            setOfEmp.insert(arr);
            arr="";
        }
    }

}
void WriteSecondryFile(){
    secondryFile.open("secondry.txt",ios::app);
    for (auto & iter : sett){    ///loop on first pair - the deptIDs-
        if(!(iter.first.empty())){
            secondryFile<< iter.first <<"|";
            for (auto &iter2: iter.second){ ///loop on the second pair -employees vector-
                secondryFile << iter2<<'|';
            }
            secondryFile<<'\n';}
    }
    secondryFile.close();
}
void readSecondry();
void searchByDepId(char DepId[])
{
    sett.clear();
    readSecondry();
    string str=DepId;
    for(auto& iter:sett)
    {
        if(iter.first==str)
        {
            for(auto &iter2:iter.second)
            {
                char dp[13];
                strcpy(dp,iter2.c_str());
                searchByID(dp);
            }
        }
    }
}
void readSecondry(){
    sett.clear();
    secondryFile.open("secondry.txt",ios::in|ios::app);
    string str,str2;
    while (!secondryFile.eof()){
        getline(secondryFile,str,'|');///read
        getline(secondryFile,str2,'\n');///read all employes
        parseEmployeeID(str2);///separate all emp to different employe
        sett.insert({str,setOfEmp});
    }
    secondryFile.close();
}
void writePrimaryDepartment();
void primarySortDepartment(){
    sort(primaryMapDepartment.begin(),primaryMapDepartment.end());
    writePrimaryDepartment();
}
class Department {
public:

    char DepartmentId[30]=" ";// primary
    char name[50]=" ";
    char manager[50]=" ";
    friend ostream &operator<<(ostream &output, const Department &dep )
    {
        output<<"\n========department "<<dep.DepartmentId<<" info ========\n"<<"name: "<<dep.name<<"\nmanager: "<<dep.manager<<"\n";
        output<<"\n========================================================\n ";
        return output;
    }

};
struct pIndexDepartment{
    char id[30];
    int byteOfSet;
    bool operator<(const pIndex &r) const { // for the sort function
        return strcmp(id, r.id) < 0;
    }
};
void writePrimaryDepartment(){
    primaryFileDepartment.open("primaryDepartment.txt",ios::out);
    primarySortDepartment();
    for(auto &iter : primaryMapDepartment)
    {
        primaryFileDepartment<<iter.first<<'|'<<iter.second<<'\n';
    }
    primaryFileDepartment.close();
}
void readPrimaryDepartmnet(){
    primaryMapDepartment.clear();
    primaryFileDepartment.open("primaryDepartment.txt",ios::in|ios::app);
    string ID;
    string bos;
    while(!primaryFileDepartment.eof())
    {
        pIndexDepartment pi;
        getline(primaryFileDepartment,ID,'|');
        getline(primaryFileDepartment,bos,'\n');
        if (bos==""||ID=="") break;
        else{
            pi.byteOfSet= stoi(bos);
            primaryMapDepartment.push_back({ID,pi.byteOfSet});
        }
    }
    primaryFileDepartment.close();
}
int byteoffsetD=0;
void addDepartment(Department dept){
    int recSize=0;
    cout << endl << "Enter department  ID (Max 13 Letters):";
    cin >> dept.DepartmentId;
    recSize+=strlen(dept.DepartmentId);
    cout << "Enter department name (Max 30 Letters) :";
    cin >> dept.name;
    recSize+= strlen(dept.name);
    cout << "Enter department  manager (Max 50 Letters) :";
    cin >> dept.manager;
    recSize+= strlen(dept.manager);
    fileDepartment.open("dataFileDepartment.txt",ios::app);
    recSize+=countDigit(recSize)+6;
    fileDepartment<<'$'<<recSize<<'|'<<dept.DepartmentId<<'|'<<dept.name<<'|'<<dept.manager<<'|'<<endl;
    primaryFileDepartment.open("primaryDepartment.txt",ios::app);
    primaryFileDepartment<<dept.DepartmentId<<'|'<<byteoffsetD<<'\n';
    string str;
    getline(primaryFileDepartment,str,'|');
    getline(primaryFileDepartment,str, '\n');
    if(!(str=="")) {byteoffsetD= stoi(str);}
    byteoffsetD+=(recSize);
    primaryFileDepartment.close();
    fileDepartment.close();
}
int binarySearchDepartment(char id[]){
    sort(primaryMapDepartment.begin(),primaryMapDepartment.end());
    int start=0, mid, end=primaryMapDepartment.size()-1;
    while(start<=end)
    {
        mid=(start+end)/2;
        if(primaryMapDepartment[mid].first<id)
        {
            start=mid+1;
        } else if(primaryMapDepartment[mid].first>id)
        {
            end=mid-1;
        }
        else if(primaryMapDepartment[mid].first==id){
            return primaryMapDepartment[mid].second;
        }
        else{ return -1;}
    }
}
Department searchByIDDepartment(char id[]){
    Department d;
    int bos=binarySearchDepartment(id);
    //cout<<bos;
    if(bos==-1)
    {cout<<"depatment not found"; }
    else {
        fileDepartment.open("dataFileDepartment.txt", ios::in|ios::out);
        fileDepartment.unsetf(ios::skipws);
        fileDepartment.seekg(bos, ios::beg);
        string str;
        getline(fileDepartment,str,'|');
        getline(fileDepartment,str,'|');
        strcpy(d.DepartmentId,str.c_str());
        getline(fileDepartment,str,'|');
        strcpy(d.name,str.c_str());
        getline(fileDepartment,str,'|');
        strcpy(d.manager,str.c_str());
    }
    cout<<d;
    fileDepartment.close();
    return d;
}
void primaryDeletionDepartment(char ID[]){
    readPrimaryDepartmnet();
    string str;
    str=ID;
    for(int i=0;i<primaryMapDepartment.size();i++)
    {
        if(primaryMapDepartment[i].first==str)
        {
            cout<<primaryMapDepartment[i].first<<endl;
            primaryMapDepartment.erase(primaryMapDepartment.begin()+i);

        }
    }

    writePrimaryDepartment();
}
void dataFileDeletionDepartment(char ID[]){
    int bos =  binarySearchDepartment(ID);
    fileDepartment.open("dataFileDepartment.txt", ios::in|ios::out);
    fileDepartment.seekg(bos,ios::beg);
    fileDepartment.put('*');
    fileDepartment.close();
    primaryDeletionDepartment(ID);

}
void WriteSecondryFileDepartment();
void secondryStructureDepartment()
{

    fileDepartment.open("dataFileDepartment.txt",ios::out|ios::in);
    IDSDepartment.clear();
    while(!(fileDepartment.eof()))
    {
        string str,str2;
        getline(fileDepartment,str,'|');
        getline(fileDepartment,str,'|');
        getline(fileDepartment,str2,'|');
        IDSDepartment.push_back({str,str2});
        getline(fileDepartment,str,'\n');
    }
    for(auto& iter:IDSDepartment)
    {
        if(!(iter.first.empty()))
        {settDepartment.insert({iter.first,iter.second});}
    }
    int ii =0;
    /*  for(auto&iter:settDepartment)
      {
          if(!(iter.first.empty())){
          cout<<iter.first<<" "<<iter.second<<endl;
          ii++;
          }
      }
      cout<<ii;*/
    WriteSecondryFileDepartment();
    settDepartment.clear();
    fileDepartment.close();
}
void WriteSecondryFileDepartment(){
    secondryFileDepartment.open("secondryDepartment.txt",ios::app);
    for (auto & iter : settDepartment){    ///loop on first pair - the deptIDs-
        if(!(iter.first.empty())){
            secondryFileDepartment<< iter.first <<"|";
            secondryFileDepartment << iter.second<<'|';
            secondryFileDepartment<<'\n';}
    }
    secondryFileDepartment.close();
}
void readSecondryDepartment();
void searchByName(char name[])
{/*
    settDepartment.clear();
    readSecondryDepartment();
    string str=name;
    for(auto& iter:settDepartment)
    {
        if(iter.second==str)
        {
            char dp[50];
            strcpy(dp,iter.first.c_str());
            */
    searchByIDDepartment(name);

}
void readSecondryDepartment(){
    settDepartment.clear();
    secondryFile.open("secondryDepartment.txt",ios::in|ios::app);
    string str,str2;
    while (!secondryFileDepartment.eof()){
        getline(secondryFileDepartment,str,'|');///read
        getline(secondryFileDepartment,str2,'\n');///read all employes
        //parseEmployeeID(str2);///separate all emp to different employe
        settDepartment.insert({str,str2});
    }
    secondryFileDepartment.close();
}

int menu()
{
    cout<<"1-add new employee\n"
        << "2- add new department\n"<<
        "3- delete employee ID\n"<<
        "4- delete department ID\n"<<
        "5- print employee ID\n"<<
        "6- print employee department id\n"<<
        "7- print department id\n"<<
        "8- print department name\n"<<
        "9- write a query\n"<<
        "10- EXIT\n";
    int i;
    cin>>i;
    return i;
}

void parse(string s){
    vector<string>v;
    string str="";
    for(int i=0;i<s.length();i++){
        if(s[i]!=' '){
            str+=s[i];
        }else if(s[i]==' '){
            v.push_back(str);
            str="";
        }
    }
    if(v[0]=="select" && v[2]=="from" && v[4]=="where" && v[6]=="="){
        if(v[1]=="all" && v[5]=="dep_id"){
            if(v[3]=="employee"){

                char x[30];
                strcpy(x,v[7].c_str());
                searchByDepId(x);

            }else if(v[3]=="department"){

                char x[30];
                strcpy(x,v[7].c_str());
                searchByIDDepartment(x);

            }else{
                cout<<"wrong input"<<endl;
            }
        }
    }
}


int main()
{
    binarySearch("20190522");
    employee e;
    Department d;
    while(true)
    {
        int i = menu();
        if(i==1)
        {
            addEmplyee(e) ;
            secondryStructure();
            readPrimary();
            readSecondry();

        }
        else if( i==2)
        {
            addDepartment(d);
            secondryStructureDepartment();
            readPrimaryDepartmnet();
            readSecondryDepartment();
        }
        else if( i==3)
        {
            cout<<"enter employee you want to delete\n";
            char em[13];
            cin>>em;
            dataFileDeletion(em);
        }
        else if( i==4)
        {
            cout<<"enter department you want to delete\n";
            char em[30];
            cin>>em;
            dataFileDeletionDepartment(em);
        }
        else if( i==5)
        {
            readPrimary();
            cout<<"enter employee you want to search\n";
            char em[13];
            cin>>em;
            searchByID(em);
        }
        else if( i==6)
        {
            readPrimary();
            cout<<"enter employee department id you want to search\n";
            char em[30];
            cin>>em;
            searchByDepId(em);
        }
        else if( i==7)
        {
            cout<<"enter department you want to search\n";
            char em[30];
            cin>>em;
            searchByIDDepartment(em);
        }
        else if( i==8)
        {
            cout<<"enter department you want to search\n";
            char em[50];
            cin>>em;
            searchByName(em);
        }
        else if( i==9)
        {
            cout<<"enter query";
            string input;
            cin>>input;
            parse(input);

        }
        else if( i==10)
        {
            exit(0);

        }
        else {
            cout<<"choose correct choice"<<endl;
            continue;
        }
    }
}
