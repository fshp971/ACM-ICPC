import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
    final static int maxn = (int)1e5;
    static int ai[] = new int[maxn+5];
    static int bi[] = new int[maxn+5];
    static int ci[] = new int[maxn+5];
    static int di[] = new int[maxn+5];
    public static void main(String[] args) {
        InputReader in = new InputReader(System.in);
        //Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        for(int i = 1; i <= n; ++i) ai[i] = in.nextInt();
        for(int i = 1; i <= n; ++i) bi[i] = in.nextInt();
        for(int i = 1; i <= n; ++i) ci[i] = in.nextInt();
        for(int i = 1; i <= n; ++i) di[i] = in.nextInt();

        BigInteger A1 = BigInteger.ZERO, B1 = BigInteger.ZERO, C1 = BigInteger.ZERO;
        BigInteger A2 = BigInteger.ZERO, B2 = BigInteger.ZERO, C2 = BigInteger.ZERO;
        for(int i = 1; i <= n; ++i) {
            BigInteger tmp1 = BigInteger.valueOf(bi[i]-ai[i]);
            BigInteger tmp2 = BigInteger.valueOf(di[i]-ci[i]);
            BigInteger tmp3 = BigInteger.valueOf(ci[i]-ai[i]);

            A1 = A1.add( tmp1.multiply(tmp1) );
            B1 = B1.subtract( tmp1.multiply(tmp2) );
            C1 = C1.add( tmp1.multiply(tmp3) );

            A2 = A2.add( tmp2.multiply(tmp1) );
            B2 = B2.subtract( tmp2.multiply(tmp2) );
            C2 = C2.add( tmp2.multiply(tmp3) );
        }

        BigInteger a1, a2, bb;
        {
            bb = A1.multiply(B2).subtract( A2.multiply(B1) );
            if(bb.compareTo(BigInteger.ZERO)==0) {
                a1 = C1;
                a2 = BigInteger.ZERO;
                bb = A1;
            }
            else {
                a1 = C1.multiply(B2).subtract( C2.multiply(B1) );
                a2 = A1.multiply(C2).subtract( A2.multiply(C1) );
            }
        }

        BigInteger ans1 = BigInteger.ZERO, ans2 = bb.multiply(bb);
        for(int i = 1; i <= n; ++i) {
            BigInteger tmp = BigInteger.valueOf(ai[i]-ci[i]).multiply(bb);
            tmp = tmp.add( BigInteger.valueOf(bi[i]-ai[i]).multiply(a1) );
            tmp = tmp.subtract( BigInteger.valueOf(di[i]-ci[i]).multiply(a2) );
            ans1 = ans1.add( tmp.multiply(tmp) );
        }

        BigInteger g = ans1.abs().gcd(ans2.abs());
        ans1 = ans1.divide(g);
        ans2 = ans2.divide(g);
        if(ans2.compareTo(BigInteger.ZERO)<0) {
            ans1 = ans1.negate();
            ans2 = ans2.negate();
        }
        System.out.print(ans1);
        System.out.print("/");
        System.out.println(ans2);
        return;
    }

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }
    }
}
