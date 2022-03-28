import java.util.*;
import java.io.*;
import java.math.*;
public class two {
  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer t = new StringTokenizer(in.readLine());

    int time = Integer.parseInt(t.nextToken());

    int hour2 = time / 1000;
    int hour1 = (time / 100) % 10;
    int min2 = (time / 10) % 10;
    int min1 = time % 10;

    if(hour2 >= 8){
      hour2 = hour2 - 8;
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.print(" ");

    if(hour1 >= 8){
      hour1 = hour1 - 8;
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.print(" ");
    System.out.print(" ");
    System.out.print(" ");

    if(min2 >= 8){
      min2 = min2 - 8;
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.print(" ");

    if(min1 >= 8){
      min1 = min1 - 8;
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.println();

    if(hour2 >= 4){
      hour2 = hour2 - 4;
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.print(" ");

    if(hour1 >= 4){
      hour1 = hour1 - 4;
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.print(" ");
    System.out.print(" ");
    System.out.print(" ");

    if(min2 >= 4){
      min2 = min2 - 4;
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.print(" ");

    if(min1 >= 4){
      min1 = min1 - 4;
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.println();

    if(hour2 >= 2){
      hour2 = hour2 - 2;
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.print(" ");

    if(hour1 >= 2){
      hour1 = hour1 - 2;
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.print(" ");
    System.out.print(" ");
    System.out.print(" ");

    if(min2 >= 2){
      min2 = min2 - 2;
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.print(" ");

    if(min1 >= 2){
      min1 = min1 - 2;
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.println();

    if(hour2 >= 1){
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.print(" ");

    if(hour1 >= 1){
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.print(" ");
    System.out.print(" ");
    System.out.print(" ");

    if(min2 >= 1){
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.print(" ");

    if(min1 >= 1){
      System.out.print("*");
    } else {
      System.out.print(".");
    }

    System.out.println();

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
