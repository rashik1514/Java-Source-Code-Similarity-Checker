public class Word implements Comparable{
  private String word;
  public Word(String str){
    this.word = str;
  }
  public String toString(){
  return word;
  }
  public boolean equals(Object other){
    if(this.compareTo((Word) other) == 0){
      return true;
      }
    else{
     return false
     }
  }
  public int hashCode(){  // heal or beasarat
    int hc = 0;
    for(int i=0; i<word.length(); i++){
      char c = word.charAt(i);
      hc += Character.getNumericValue(c);  //Ascii value
    }
    return hc;
  }
  public int compareTo(Word w){
    return (word.compareToIgnoreCase(w.word));
  }
}
