#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <stdlib.h>
#include <set>
#include <iterator>
#include <queue>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <windows.h>
//#include "initialization.cpp"
#include "trim.cpp"
#include "fileMaker.h"

using namespace std;

struct variables{
  string type;
  string realName;
  string fakeName;

};

struct builtInFunction{
    string name;
    vector <string> content;

};

struct info{
    string returnType, accessMod;
    vector <pair<string, string> >parameters;
    string name;
    string contentWithSpaces;
    string contentWithoutSpaces;
    vector<string> contentWithLines;
    vector<string> contentWithFakeLines;
    vector<variables> infoOfVariables;
    vector<builtInFunction> builtInFunct;
};

struct wholeClass{
  string name;
  string accessMod;
  vector <pair<string, string> > other;
  vector<info> methodsOfCode;
};

struct List {
	vector<string> files;
	vector<string> folders;
};

set <string> accessModifiers;
set <string> type;
set <string> builtInFunc;
queue<string> fakeInt;
queue<string> fakeChar;
queue<string> fakeDouble;
queue<string> fakeString;



/*struct List lsfiles(string folder){

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

void loadProjects(){
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
*/

void initiaization(){
  accessModifiers.insert("public");
  accessModifiers.insert("private");
  accessModifiers.insert("protected");

  type.insert("int");
  type.insert("double");
  type.insert("String");
  type.insert("void");
  type.insert("char");
  type.insert("boolean");
  type.insert("int[]");
  type.insert("double[]");
  type.insert("boolean[]");
  type.insert("String[]");
  type.insert("char[]");
  type.insert("int[][]");
  type.insert("double[][]");
  type.insert("boolean[][]");
  type.insert("String[][]");
  type.insert("char[][]");

  builtInFunc.insert("for");
  builtInFunc.insert("while");
  builtInFunc.insert("do");
  builtInFunc.insert("if");
  builtInFunc.insert("else");

  fakeInt.push("i1");
  fakeInt.push("i2");
  fakeInt.push("i3");
  fakeInt.push("i4");
  fakeInt.push("i5");
  fakeInt.push("i6");
  fakeInt.push("i7");
  fakeInt.push("i8");
  fakeInt.push("i9");
  fakeInt.push("i10");

  fakeString.push("s1");
  fakeString.push("s2");
  fakeString.push("s3");
  fakeString.push("s4");
  fakeString.push("s5");
  fakeString.push("s6");
  fakeString.push("s7");
  fakeString.push("s8");
  fakeString.push("s9");

  fakeDouble.push("d1");
  fakeDouble.push("d2");
  fakeDouble.push("d3");
  fakeDouble.push("d4");
  fakeDouble.push("d5");
  fakeDouble.push("d6");
  fakeDouble.push("d7");
  fakeDouble.push("d8");
  fakeDouble.push("d9");

  fakeChar.push("c1");
  fakeChar.push("c2");
  fakeChar.push("c3");
  fakeChar.push("c4");
  fakeChar.push("c5");
  fakeChar.push("c6");
  fakeChar.push("c7");
  fakeChar.push("c8");
  fakeChar.push("c9");

}

void clearQueue(queue<string> q){
  while (!q.empty())
    {
        q.pop();
    }
}

void clearAll(){
  clearQueue(fakeInt);
  clearQueue(fakeDouble);
  clearQueue(fakeChar);
  clearQueue(fakeString);
}



void makeTemporaryFile(string fileName, string outFileName){
  bool classNamePassed = false;
  ifstream inFile(fileName.c_str());
  ofstream oFile(outFileName.c_str());

  if(inFile.is_open()) {
      string line;
      getline(inFile,line);

      while(!inFile.eof()){
          if(line.find("class") != string::npos) classNamePassed = true;
          string tempLine = commentFreeFileInput(line);
          if(tempLine != "" && classNamePassed) oFile << line << endl;
          getline(inFile, line);
      }
  }
  inFile.close();
  oFile.close();
}

info infoExtractor(string s){
  info methodsOfCode;
  istringstream iss(s);
  string temp, iType, iName;
  iss >> temp;

  if(accessModifiers.find(temp) != accessModifiers.end()){
    methodsOfCode.accessMod = temp;
    iss >> temp;
    if(temp == "static"){
      iss >> temp;
      if(type.find(temp) != type.end()){
        methodsOfCode.returnType = temp;
        iss >> temp;
        methodsOfCode.name = temp;
      }
      else methodsOfCode.name = temp;
    }
    else if(type.find(temp) != type.end()){
      methodsOfCode.returnType = temp;
      iss >> temp;
      methodsOfCode.name = temp;
    }
    else methodsOfCode.name = temp;
   }

   else{
    if(type.find(temp) != type.end()){
      methodsOfCode.returnType = temp;
      iss >> temp;
      methodsOfCode.name = temp;
    }
    else methodsOfCode.name = temp;
   }
  iss >> temp;
  iss >> temp;
  bool commaFound;
  pair<string, string> pairTemp;
  while(true){
    if(type.find(temp) != type.end()){
      pairTemp.first = temp;
      iss >> temp;
      pairTemp.second = temp;
      methodsOfCode.parameters.push_back(pairTemp);
      iss >> temp;
      if(temp == ")") break;
      else iss >> temp;
    }
    else break;
  }

  return methodsOfCode;
}

wholeClass extractClassInfo(string s){
  istringstream iss(s);
  string temp;
  wholeClass wC;
  pair<string, string> vs;

  while(iss >> temp){
      if(temp == "public"){
         wC.accessMod = temp;
         iss >> temp;
         iss >> temp;
         wC.name = temp;
       }
      else if(temp == "class"){
         iss >> temp;
         wC.name = temp;
      }
      if(temp == "{") return wC;
      else{
        vs.first = temp;
        iss >> temp;
        vs.second = temp;
        wC.other.push_back(vs);
      }

  }
}

string addSpacesAroundFirstBrackets(string s){
  string temp="";
  for(int i=0; i<s.length(); i++){
    if(s[i]=='(' || s[i]==')' || s[i]=='{' || s[i]==',' ||
      s[i]==';' || s[i]=='}' || s[i]=='='|| s[i]=='+'|| s[i]=='-'|| s[i]=='<'|| s[i]=='>') temp += " " + string(1,s[i]) + " ";
    else temp += s[i];
  }
  return temp;
}

bool onlyBracketPresent(string s){
  for(int i=0; i<s.length(); i++){
    if (s[i] == ' ' || s[i] == 9){
        continue;
    }
    if(s[i] == '{' ) return true;
    else return false;
  }
}


bool bracketPresent(string s){
  for(int i=0; i<s.length(); i++){
    if(s[i] == '{' || s[i] == '}') return true;
  }
  return false;
}

string makingSureOneSpace(string s){
  istringstream iss(s);
  string  temp,content="";
  while(iss >> temp){
    content += temp+" ";
  }
  return  trim(content);
}


char whichBracketPresent(string s){
  for(int i=0; i<s.length(); i++){
    if(s[i] == '{'  ) return '{';
    else if(s[i] == '}') return '}';
  }
}

string delSpaces(string &str) {
   str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
   return str;
}

void printVectorVariables(vector<variables> v){
  for(int i=0; i<v.size(); i++){
    cout << v[i].type << ' ' << v[i].realName << ' ' << v[i].fakeName<<endl;
  }
}

bool isInteger(string s){
  for(int i=0; i<s.length(); i++){
    if((s[i]>=65 && s[i]<=90) || (s[i]>=97 && s[i]<=122)) return false;
  }
  return true;
}

bool isCharInitializer(string s){
  for(int i=0; i<s.length(); i++){
    if(s[i] == 39) return true;
    return false;
  }
}

bool isStringInitializer(string s){
  for(int i=0; i<s.length(); i++){
    if(s[i] == 34) return true;
    return false;
  }

}

vector<variables> extractVariables(vector<string> s){
  vector<variables> var;
  variables tempVar;
  queue<string> tempQ;
  string temp;
  bool inTheSameLine = false;

  for(int i=0; i<s.size(); i++){
    istringstream iss(s[i]);
    while(iss >> temp){
      if(type.find(temp) != type.end()){
        string type = temp; //cout << type << endl;
        while(iss >> temp){
          if(temp == ";") break;
          else if(temp != "," && temp != "=" && !isInteger(temp) && !isCharInitializer(temp) && !isStringInitializer(temp)){

             string realName = temp; //cout << realName << endl;
             tempVar.type = type;
             tempVar.realName = realName;

             if(type == "int"){
                tempVar.fakeName = fakeInt.front(); //cout << tempVar.fakeName << endl;
                fakeInt.pop();
              }
             else if(type == "double"){
               tempVar.fakeName = fakeDouble.front(); //cout << tempVar.fakeName << endl;
               fakeDouble.pop();
             }
             else if(type == "String"){
                tempVar.fakeName = fakeString.front(); //cout << tempVar.fakeName << endl;
                fakeString.pop();
              }
             else if(type == "char"){
                tempVar.fakeName = fakeChar.front(); //cout << tempVar.fakeName << endl;
                fakeChar.pop();
              }
             var.push_back(tempVar);
          }
        }
      }
    }
  }
  return var;
}

vector<string> replacingWithFakeName(vector<string> lines, vector<variables> var){
  string temp;
  string tempLine = "";
  for(int i=0; i<var.size(); i++){
    for(int j=0; j<lines.size(); j++){
      istringstream iss(lines[j]);
      while(iss >> temp){
        if(temp == var[i].realName){
          tempLine  += " " + var[i].fakeName + " ";
        }
        else tempLine += " " + temp + " ";
      }
      lines[j] = trim(makingSureOneSpace(tempLine));
      tempLine = "";
    }
  }
  clearAll();
  initiaization();
  return lines;
}

wholeClass convertTheWholeToStructVector(string fileName){

  vector <info> methodsOfCode;
  wholeClass wC;
  string line, lineBeforeBracket="";
  int lineNumber=0;
  bool classPassed = false;
  bool methodPassed = false;
  int bracketIndicator=0;
  string content="";
  string hudai;

  ifstream myfile(fileName.c_str());

  if (!myfile.is_open()){
      cout << "file not found" << endl;
      exit(1);
  }
  while(getline(myfile, line) ){
      lineNumber++;
      if(bracketPresent(line) && !classPassed){
          classPassed = true;
          wC = extractClassInfo(addSpacesAroundFirstBrackets(line));
          bracketIndicator++;
      }

      else if(bracketPresent(line) && !methodPassed && whichBracketPresent(line) == '{'){
        bracketIndicator++;
        methodPassed = true;
        //cout << line << endl;
        methodsOfCode.push_back(infoExtractor(addSpacesAroundFirstBrackets(trim(line))));
        while(bracketIndicator > 1){

          getline(myfile, line);
          methodsOfCode.back().contentWithLines.push_back(makingSureOneSpace(addSpacesAroundFirstBrackets(trim(line))));
          if(bracketPresent(line)){
            if(whichBracketPresent(line) == '{') bracketIndicator++;
            else bracketIndicator--;
            content += " " + addSpacesAroundFirstBrackets(trim(line)) + " ";
          }
          else content += addSpacesAroundFirstBrackets(trim(line));
        }

       methodsOfCode.back().contentWithSpaces = content;
       methodsOfCode.back().infoOfVariables = extractVariables(methodsOfCode.back().contentWithLines);
       methodsOfCode.back().contentWithFakeLines = replacingWithFakeName(methodsOfCode.back().contentWithLines, methodsOfCode.back().infoOfVariables);
       methodsOfCode.back().contentWithoutSpaces = delSpaces(content);
       methodPassed = false;
       content = "";
      }
  }
  wC.methodsOfCode = methodsOfCode;
  return wC;
}

void printAllContentOfStructVector(wholeClass wC){

  cout << "Class name: " << wC.name << endl;
  cout << "Class access modifier: " << wC.accessMod << endl;

  for(int i=0; i<wC.methodsOfCode.size(); i++){
      cout<<"Method name: "<< wC.methodsOfCode[i].name<<endl;
      cout<<"Method Return type: "<< wC.methodsOfCode[i].returnType<<endl;
      cout<<"Method accessMod: "<< wC.methodsOfCode[i].accessMod<<endl;
      cout << "Parameters:-" << endl;
      vector<pair<string,string> > temp;
      temp = wC.methodsOfCode[i].parameters;
      for(int j = 0; j < temp.size(); j++){
        cout << temp[j].first << " " << temp[j].second << endl;
      }
      cout << wC.methodsOfCode[i].contentWithSpaces <<endl;
      for(int j = 0; j < wC.methodsOfCode[i].contentWithLines.size(); j++){
        cout << wC.methodsOfCode[i].contentWithLines[j] << endl;
      }
      cout << wC.methodsOfCode[i].contentWithoutSpaces <<endl;
      printVectorVariables(wC.methodsOfCode[i].infoOfVariables);

      for(int j = 0; j < wC.methodsOfCode[i].contentWithFakeLines.size(); j++){
        cout << wC.methodsOfCode[i].contentWithFakeLines[j] << endl;
      }
      cout << endl;
    }
}

void exactMatchingLineByLineOfTwoFiles(string file1, string file2){

  wholeClass v1, v2;
  vector<info> methodsOfCode1;
  vector<info> methodsOfCode2;
  bool deleteIt = false;
  v1 = convertTheWholeToStructVector(file1);
  v2 = convertTheWholeToStructVector(file2);
  methodsOfCode1 = v1.methodsOfCode;
  methodsOfCode2 = v2.methodsOfCode;
  printAllContentOfStructVector(v1);
  printAllContentOfStructVector(v2);

  for(int i=0; i<methodsOfCode1.size(); i++){
    for(int j=0; j<methodsOfCode2.size(); j++){
      if(methodsOfCode1[i].name == methodsOfCode2[j].name){
        cout << "name matched" << endl;
      }
      if(methodsOfCode1[i].returnType == methodsOfCode2[j].returnType){
        cout << "Return type matched" << endl;
      }
      if(methodsOfCode1[i].accessMod == methodsOfCode2[j].accessMod){
        cout << "access modifiers matched" << endl;
      }
      if(methodsOfCode1[i].parameters.size() == methodsOfCode2[j].parameters.size()){
        cout << "Number of parameters matched" << endl;
        for(int k=0; k<methodsOfCode1[i].parameters.size(); k++){
          for(int l=0; l<methodsOfCode2[j].parameters.size(); l++){
            if(methodsOfCode1[i].parameters[k].first == methodsOfCode2[j].parameters[l].first ){
              cout << methodsOfCode1[i].parameters[k].first<<"-- matched with --" << methodsOfCode2[j].parameters[l].first << endl;
              methodsOfCode1[i].parameters.erase(methodsOfCode1[i].parameters.begin()+k);
              methodsOfCode2[j].parameters.erase(methodsOfCode2[j].parameters.begin()+l);
            }
            if(methodsOfCode1[i].parameters[k].second == methodsOfCode2[j].parameters[l].second ){
              cout << methodsOfCode1[i].parameters[k].second<<"-- matched with --" << methodsOfCode2[j].parameters[l].second << endl;
            }

          }
        }
      }
    }
  }

  for(int i=0; i<methodsOfCode1.size(); i++){
    for(int j=0; j<methodsOfCode2.size(); j++){
      for(int k=0; k<methodsOfCode1[i].contentWithFakeLines.size(); k++){
        for(int l=0; l<methodsOfCode2[j].contentWithFakeLines.size(); l++){
          if(methodsOfCode1[i].contentWithFakeLines[k] == methodsOfCode2[j].contentWithFakeLines[l] ){
            if(trim(methodsOfCode1[i].contentWithFakeLines[k]) != "}" && methodsOfCode2[j].contentWithFakeLines[l] != "}"){
              cout << methodsOfCode1[i].contentWithFakeLines[k]<<"-- matched with --" << methodsOfCode2[j].contentWithFakeLines[l] << endl;
            }
          }
        }
      }
    }
  }

}

void normalisation(){

}





int main(){

        initiaization();
        //printAllContentOfStructVector(convertTheWholeToStructVector("Temp1.java"));
        //printAllContentOfStructVector(convertTheWholeToStructVector("Temp2.java"));
        exactMatchingLineByLineOfTwoFiles("Temp2.java", "Temp1.java");
        //makeTemporaryFile("test1.java","temp.java");


    return 0;
}
