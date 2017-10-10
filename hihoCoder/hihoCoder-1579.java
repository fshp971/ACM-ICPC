import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    static final int maxn = (int)1e5;
    static BigInteger Calc(int l, int r) {
        BigInteger res = BigInteger.ONE;
        for(int i = l; i <= r; ++i)
            res = res.multiply(BigInteger.valueOf(i));
        return res;
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int T = in.nextInt(), n, u;
        int[] P = new int[maxn + 5], R1 = new int[maxn + 5];
        for(; T > 0; --T) {
            n = in.nextInt();
            for(int i = 1; i <= n; ++i) {
                P[i] = in.nextInt();
                R1[P[i]] = i;
            }
            int dd = 0;
            R1[n + 1] = 0;
            for(int i = 1; i < n; ++i)
                if(R1[P[i] + 1] > R1[P[i + 1] + 1])
                    ++dd;
            if(dd > 25) { System.out.println("0"); continue; }
            int n1 = n + 26 - dd - 1, n2 = 26 - dd - 1;
            System.out.println(Calc(n1 - n2 + 1, n1).divide(Calc(1, n2)));
        }
    }
}
