#include<bits/stdc++.h>

using namespace std;

bool multipleCommentLineFlag = false;

string commentFreeFileInput(string line) {

    if(line[0]=='#') {
        return "";
    }
    if(line.length() == 0 ) {
        return "";
    }

    bool doubleQuote = false;

    int lineSize = line.size();
    for(int i=0; i < lineSize ; i++) {

        if(line[i] == '"' && doubleQuote == false) doubleQuote = true;
        else if(doubleQuote == true) {

            if(line[i] == '"') doubleQuote = false;
            else continue;
        }
        else if(multipleCommentLineFlag == true) {
            if(line[i]=='*' && line[i+1] =='/') {
                multipleCommentLineFlag = false;
                line[i] = ' ';
                line[i+1]= ' ';
            }
            else line[i]=' ';
        }
        else if(line[i]=='/' && line[i+1] =='*') {
            multipleCommentLineFlag = true;
            line[i] = ' ';
            line[i+1] = ' ';
        }
        else if(line[i] == '/' && line[i+1] == '/') {
            for(int j=i ; j<lineSize; j++) line[j] = ' ';
            break;
        }
    }
    for(int i=0; i<lineSize; i++) {
        if(line[i] != ' ' && line[i] != 13) return line+"\n";
    }
    return "";
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
