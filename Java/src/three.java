import java.util.*;
import java.io.*;
import java.math.*;
public class three {
  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer t = new StringTokenizer(in.readLine());

    int small = Integer.parseInt(t.nextToken());

    int large = Integer.parseInt(t.nextToken());

    t = new StringTokenizer(in.readLine());

    String temp = t.nextToken();

    boolean one = false;
    boolean two = false;
    boolean three = false;
    boolean four = false;

    if(temp.charAt(0) == 'A'){
      one = true;
    }
    if(temp.charAt(1) == 'A'){
      two = true;
    }
    if(temp.charAt(2) == 'A'){
      three = true;
    }
    if(temp.charAt(3) == 'A'){
      four = true;
    }

    if(one && two){
      if(large == 7 && small <= 6){
        System.out.println(8 + " " + 9);
      } else {
        System.out.println(-1);
      }
    } else if(one && three){
      if(small == 6 && large == 8){
        System.out.println(7 + " " + 9);
      } else {
        System.out.println(-1);
      }
    } else if(one && four){
      if(large - small == 3){
        System.out.println((small + 1) + " " + (small + 2));
      } else {
        System.out.println(-1);
      }
    } else if(two && three){
      if(small == 2 && large == 8){
        System.out.println(1 + " " + 9);
      } else {
        System.out.println(-1);
      }
    } else if(two && four){
      if(small == 2 && large == 4){
        System.out.println(1 + " " + 3);
      } else {
        System.out.println(-1);
      }
    } else if (three && four){
      if(small == 3 && large >= 4){
        System.out.println(1 + " " + 2);
      } else {
        System.out.println(-1);
      }
    } else {
      System.out.println(-1);
    }

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