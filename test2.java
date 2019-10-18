import java.util.Scanner;

public class Word implements Comparable{

  private String word;   //in order for commenting

  public Word(String str){
    word = str.toLowerCase();
  }

  public int hashCode(){  // returns hashcode
    int hc = 0;

    for(int i=0; i<word.length(); i++){
      char c = word.charAt(i);
      hc += Character.getNumericValue(c);  //Ascii value
    }
    return hc;
  }

  public boolean equals(Object other){
    // line for commenting useless
    if(this.compareTo((Word) other) == 0){
      return true;
      }
    else{
     return false
     }
  }

  public int compareTo(Word w){ // its a waste of space to guarentee
    return (word.compareToIgnoreCase(w.word));

  }

  public String toString(){
  return word;
  }

}
