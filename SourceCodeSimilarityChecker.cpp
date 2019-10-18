#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <windows.h>

using namespace std;

vector<string> project1, project2;

struct info{
    string returnType;
    pair<string, string> parameters[5];
    string name;
    string content;

}methodsOfCode1[10], methodsOfCode2[10];

struct List {
	vector<string> files;
	vector<string> folders;
};

struct List lsfiles(string folder)
{
    vector<string> files;
	vector<string> folders;
    char search_path[200];
    sprintf(search_path, "%s*.*", folder.c_str());
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path, &fd);
    if(hFind != INVALID_HANDLE_VALUE){
        do{
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
                files.push_back(fd.cFileName);

            else
				folders.push_back(fd.cFileName);

          }while(::FindNextFile(hFind, &fd));
          ::FindClose(hFind);
    }
	List me;
	me.files = files;
	me.folders = folders;

    return me;
}


void printAllBeforeSlashAsterisk(string temp,ifstream *myfile){

    for(int i=0; i<temp.length(); i++)
    {
        if(temp[i]=='/' && temp[i+1]=='*') break;
        cout<<temp[i];
    }
    cout<<endl;
}

bool isClassNamePassed(string line){

    bool flag=false;
        for(int i=0; i<line.length(); i++)
            if(line[i] == '{'){
                flag=true;
                break;
            }
    return flag;
}

bool findingTheFirstMethod(string line){

    bool found = false;
    istringstream iss(line);
    string temp;
    while(iss >> temp){
        if(temp == "public"){
            found = true;
            break;
        }
    }
    return found;
}

bool bracketPresent(string line){

    bool flag=false;
        for(int i=0; i<line.length(); i++){
            if(line[i] =='}' || line[i] == '{'){
                flag=true;
                break;
            }
        }
    return flag;
}


bool whichBracketPresent(string s){

        for(int i=0; i<s.length(); i++)
            if(s[i] =='{')
                return true;

    return false;
}


bool slashesAndAsteriskPresent(string temp){

    for(int i=0; i<temp.length(); i++)
            if(temp[i]=='/' && temp[i+1]=='*') return true;

    return false;

}

bool doubleSlashesAtMiddle(string temp){

        for(int i=0; i<temp.length(); i++)
            if(temp[i]=='/' && temp[i+1]=='/') return true;

    return false;
}


bool spacesAndSlashesAtFirst(string s){

    bool flag = false;
        for(int i=0; i<s.length(); i++){
            if(s[i] ==' '){
                if(s[i+1]=='/' && s[i+2]=='/'){
                    flag = true;
                    break;
                }
            }
            else break;
        }

    return flag;
}


bool onlySpacesAndBrackets(string s){

    bool flag = true;
        for(int i=0; i<s.length(); i++)
            if(s[i] !=' ' || s[i] != '}' || s[i]!= '{')
                return false;

    return flag;
}

void makeTemporaryFiles(string file[]){

    string line, temp;
    int lines=0;

    //string a[2] = {"First","Second"};
    string b[2] = {"Temp1.java","Temp2.java"};
//    string file[2];

    for(int i=0; i<2; i++){
        //cout<<"Enter the directory of the "<<a[i]<<" file"<<endl;
        //cin>>file[i];
        ifstream myfile(file[i].c_str());
        ofstream hisfile(b[i].c_str());

        //ifstream myfile("compare.c");

        if (myfile.is_open()){
            while ( getline (myfile, temp) ){
                if( ){
                    hisfile << temp <<endl;
                    while(getline (myfile, temp)){
                        //delete comment line and empty line//
                        if (temp[0] != '\n' && temp.length() >= 1 && temp[0] != '/' /*&& temp[0] != '{' && temp[0] != '}'*/){

                            if(temp[0]==' ' || temp[0] == '}' || temp[0] == '/'){        // Looking for '}'
                                if(onlySpacesAndBrackets(temp))
                                else if(spacesAndSlashesAtFirst(temp))
                                else if(doubleSlashesAtMiddle(temp)){                    ///////////// if comment is present after a line/////////////
                                    for(int i=0; i<temp.length(); i++){
                                        if(temp[i]=='/' && temp[i+1]=='/') break;
                                        hisfile<<temp[i];
                                    }
                                    hisfile<<endl;
                                }

                                else if(slashesAndAsteriskPresent(temp)){
                                    char ch;
                                    for(int i=0; i<temp.length(); i++){
                                        if(temp[i]=='/' && temp[i+1]=='*') break;
                                        hisfile<<temp[i];
                                    }
                                    hisfile<<endl;
                                    while(myfile >> ch){
                                        if(ch == '/'){
                                            myfile >> ch;
                                            if(ch == '*'){
                                                while(myfile >> ch){
                                                    if(ch == '*'){
                                                        myfile >> ch;
                                                        if(ch == '/') break;
                                                    }
                                                }
                                            }
                                        }
                                        else  hisfile << ch ;
                                    }
                                }
                                else hisfile<<temp<<endl;
                            }
                            else{
                                if(doubleSlashesAtMiddle(temp)){
                                    for(int i=0; i<temp.length(); i++){
                                        if(temp[i]=='/' && temp[i+1]=='/') break;
                                        hisfile<<temp[i];
                                    }
                                    hisfile<<endl;
                                }
                                if(onlySpacesAndBrackets(temp))
                                    continue;
                                else{
                                    hisfile << temp <<endl;
                                    lines++;
                                }

                            }
                        }
                    }
                }        //cout<<"Number of Lines: "<<lines<<endl;
            }
        }

        else cout << "Unable to open file";
    }
}

void matchingLineByLine(string file[]){

    string temp;
    string b[2] = {"Temp1.java","Temp2.java"};
    ifstream myfile(file[0].c_str());
    vector <string> v1,v2;
    int count = 0;
    int numberOfLines1=0, numberOfLines2=0;

    if(myfile.is_open()){
        while(getline(myfile,temp)){
            v1.push_back(temp);
            numberOfLines1++;
        }
    }
    else cout << "Cannot open file "<<endl;
    myfile.close();

    ifstream myfile1(file[1].c_str());
    ofstream outputFile("resultOnExactLineMatching.txt ");

    if(myfile1.is_open())
        while(getline(myfile1,temp)){
            //cout << temp << endl;
            v2.push_back(temp);
            numberOfLines2++;
        }
    else cout << "Cannot open file "<<endl;


    for(int i=0; i<v1.size(); i++)
        for(int j=0; j<v2.size(); j++)
            if(v1[i] == v2[j]){
                count++;
                outputFile<<"Line number "<<i<< "th of "<<file[0]<<" file found matched at line number "<<j<<"th of "<<file[1] <<" file"<<endl;
                break;
            }

    //cout << (count/(numberOfLines1+numberOfLines2))*100 <<endl;
    //cout << count <<' '<< numberOfLines1+numberOfLines2<<endl;
    double x = count/(numberOfLines1+numberOfLines2);
    cout << "Lines matched "<<count<<" out of " << numberOfLines1+numberOfLines2<<" lines" << endl;
    myfile.close();
    outputFile.close();

}


void loadProjects()
{
    string where;
    cout << "Enter the directories of both the project" << endl;
    for(int i=0; i<2; i++)
    {
        int count = 0;
        string temp;
        //cin >> where;
        if(i == 0) where="AirlineTicketManager\\src\\ticketManagerInterface\\";

        else where="AirlineTicketManager\\src\\classAssigner\\";
        //string where="AirlineTicketManager\\src\\classAssigner\\", argv = "";
        //cin >> a;
        //if(where.length() > 1){where = argv + string("\\");}else{where = "";}
        List you = lsfiles(where);                            //Get contents of directory

        vector<string>::iterator files_begin = you.files.begin();
        vector<string>::iterator files_end = you.files.end();
        vector<string>::iterator folders_begin = you.folders.begin();
        vector<string>::iterator folders_end = you.folders.end();
        for(; folders_begin != folders_end; folders_begin++){
            //cout << "[D] " << *folders_begin << "\n";
        }
        for(; files_begin != files_end; files_begin++){
            //cout << *files_begin << "\n";
            temp = where+*files_begin;
            if(i == 0) project1.push_back(temp) ;

            else  project2.push_back(temp);
            count++;
        }

        //cout << count << endl;

    }


}


int main () {

    loadProjects();

    string file[2], temp ;
    file[0] = "with.java"; file[1] = "compare.java";
    makeTemporaryFiles(file);


    /*for(int i=0; i<project1.size(); i++)
    {
        for(int j=0; j<project2.size(); j++)
        {
            file[0] = project1[i];
            file[1] = project2[j];

            cout << "Matching "<<file[0]<<" with "<< file[1] << endl;

            makeTemporaryFiles(file);
            matchingLineByLine(file);
            //matchingCharByChar();

        }
    }*/




    return 0;
}
