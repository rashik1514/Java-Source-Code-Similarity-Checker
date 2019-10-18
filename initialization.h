#include <queue>
#include <set>
#include <string>
#include<iostream>

using namespace std;

set <string> accessModifiers;
set <string> type;
set <string> builtInFunc;
queue<string> fakeInt;
queue<string> fakeChar;
queue<string> fakeDouble;
queue<string> fakeString;

//bool multipleCommentLineFlag = false;
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
