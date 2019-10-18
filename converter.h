#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

string delSpaces(string &str) {
   str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
   return str;
}

char whichBracketPresent(string s){
  for(int i=0; i<s.length(); i++){
    if(s[i] == '{'  ) return '{';
    else if(s[i] == '}') return '}';
  }
}

string makingSureOneSpace(string s){
  istringstream iss(s);
  string  temp,content="";
  while(iss >> temp){
    content += temp+" ";
  }
  return  trim(content);
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

void printVectorVariables(vector<variables> v){
  for(int i=0; i<v.size(); i++){
    cout << v[i].type << ' ' << v[i].realName << ' ' << v[i].fakeName<<endl;
  }
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
