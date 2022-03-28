import java.util.*;
import java.io.*;
import java.math.*;
public class four {
  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer t = new StringTokenizer(in.readLine());

    int n = Integer.parseInt(t.nextToken());

    long[] time = new long[n];
    long[] packet = new long[n];

    for(int i = 0; i < n; i++){
      t = new StringTokenizer(in.readLine());

      time[i] = Integer.parseInt(t.nextToken());
      packet[i] = Integer.parseInt(t.nextToken());
    }

    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        if(packet[j] == i){
          long temp1 = packet[j];
          long temp2 = packet[i];
          packet[i] = temp1;
          packet[j] = temp2;

          temp1 = time[i];
          temp2 = time[j];
          time[i] = temp2;
          time[j] = temp1;
        }
      }
    }

    long solution = 0;

    for(int i = 0; i < n; i++){
      if(packet[i] + solution < time[i]){
        solution = time[i] - packet[i];
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