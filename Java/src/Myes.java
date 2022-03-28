import java.math.*;
import java.util.*;
import java.io.*;
public class Myes {
  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer t = new StringTokenizer(in.readLine());

    int[] a = new int[10];

    for(int i = 0; i < 10; i++){
      a[i] = Integer.parseInt(t.nextToken());
    }

    t = new StringTokenizer(in.readLine());

    int n = Integer.parseInt(t.nextToken());

    BigInteger product = BigInteger.valueOf(1);

    int good = 0;

    for(int i = 0; i < 10; i++){
      if(a[i] != 0){
        good++;
      }
    }

    if(good < n){
      System.out.println(0);
    } else {
      for(int i = 0; i < 10; i++){
        if(a[i] != 0 && n > 0){
          n--;
          product = product.multiply(BigInteger.valueOf(a[i]));
        }
      }
      System.out.println(product);
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