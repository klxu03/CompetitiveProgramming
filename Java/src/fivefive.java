import java.util.*;
import java.io.*;
import java.math.*;
public class fivefive {
  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer t = new StringTokenizer(in.readLine());

    int[] primes = new int[100000];
    int[] sieve = new int[1299712];

    Arrays.fill(sieve, 0);

    for(int x = 2; x <= 1299711; x++){
      if(sieve[x] != 0){
        continue;
      }
      for(int u = 2*x; u <= 1299711; u+= x){
        sieve[u] = x;
      }
    }

    int counter = 0;
    for (int i = 2; i < 1299711; i++) {
      if (sieve[i] == 0) {
        primes[counter] = i;
        counter++;
      }
    }


    // implement sieve out
    // largest num: 1299710


    int small = Integer.parseInt(t.nextToken());
    int large = Integer.parseInt(t.nextToken());

    t = new StringTokenizer(in.readLine());

    String temp = t.nextToken();

    small--;
    large--;

    int solution = 0;

    for(int i = small; i <= large; i++){
      String prime = Integer.toString(primes[i]);
      if(prime.contains(temp)){
        solution++;
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
