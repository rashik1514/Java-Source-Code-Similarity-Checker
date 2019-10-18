public class Word implements Comparable{
  private String word;

  /**
  *It's an object file
  so it will be tested.
  */
  public Word(String str){
    this.word = str;
  }

  /**
    Retuens the word
    @return string
  */
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

  /**
  *compute and return hashcode for the word
  *@return int hashcode
  */

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
