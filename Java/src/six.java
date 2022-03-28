import java.util.*;
import java.io.*;
import java.math.*;
public class six {
  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer t = new StringTokenizer(in.readLine());

    String temp = t.nextToken();

    boolean changed = true;

    while(changed){
      changed = false;

      for(int i = 0; i < temp.length()-1; i++){
        if(temp.charAt(i) == '(' && temp.charAt(i+1) == ')'){
          temp = temp.substring(0, i) + temp.substring(i+2);
          changed = true;
        } else if (temp.charAt(i) == '[' && temp.charAt(i+1) == ']'){
          temp = temp.substring(0, i) + temp.substring(i+2);
          changed = true;
        } else if (temp.charAt(i) == '<' && temp.charAt(i+1) == '>'){
          temp = temp.substring(0, i) + temp.substring(i+2);
          changed = true;
        } else if (temp.charAt(i) == '{' && temp.charAt(i+1) == '}'){
          temp = temp.substring(0, i) + temp.substring(i+2);
          changed = true;
        }
      }
    }

    int open = 0;
    int closed = 0;

    int question = 0;

    for(int i = 0; i < temp.length(); i++){
      if(temp.charAt(i) == '?'){
        question++;
      }
    }

    int[] possible = new int[question];

    int solution = 1;

    int hmm = 0;

    boolean good = true;

    for(int i = 0; i < temp.length(); i++){
      char next = temp.charAt(i);

      if(next == '(' || next == '{' || next == '<' || next == '['){
        open++;
        hmm = 0;
        closed = 0;
      } else if (next == '?'){
        hmm++;
      } else {
        if(open == 0 && hmm == 0){
          good = false;
          solution = 0;
          break;
        } else if(open != 0){
          if(hmm % 2 == 1){
            solution = 0;
            break;
          } else {
            solution = solution * 4;
          }
        } else{

        }
      }

    }

    System.out.println(solution);

    in.close();
  }
}
// Important Things:
/* Integer.parseInt(t.nextToken());
 * t.nextToken();
 * t = new StringTokenizer(in.readLine());
 * Integer.parseInt(t.nextToken());
 * Long.parseLong(t.nextToken());
 * Double.parseDouble(t.nextToken());
 * out.println(x + " " + y);
 * String place [] = new String [N];
 * int traffic [][] = new int [N][2];
 * in.readLine();
 * Integer.parseInt(in.readLine());
 * String ret = "";
 * ArrayList<String> x = new ArrayList<String>();
 * BufferedReader in = new BufferedReader(new FileReader("BASE.in"));
 * PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("BASE.out")));
 * StringTokenizer t = new StringTokenizer(in.readLine());
 * in.close();
 * out.close();
 * BigInteger product = BigInteger.valueOf(0);
 * A.add(BigInteger.valueOf(val));
 * A.intValue();
 * A.compareTo(B)
 * A.equals(B)
 * A.multiply(BigInteger.valueof(i));
 * word.charAt(i) == 's'
 * Math.pow(R,2) * Math.PI;
 * StringBuffer answer = new StringBuffer();
 * answer.append("" + max);
 * str1.equals(str2);
 * str2.equalsIgnoreCase(str1);
 * int str1.compareTo(String str2) (if 1 > 2 returns positive answer)
 * DecimalFormat DF = new DecimalFormat("###.##");
 * System.out.println("x = " + DF.format(x));
 */