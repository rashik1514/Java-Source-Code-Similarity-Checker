#include<string>
#include <vector>


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
