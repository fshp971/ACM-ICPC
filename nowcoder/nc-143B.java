import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
    static BigInteger[] seg = new BigInteger[5000];
    static BigInteger lim;
    static int tot = 0;

    static void Pre() {
        lim = BigInteger.valueOf(10);
        lim = lim.pow(1000);
        BigInteger t = BigInteger.valueOf(3);
        BigInteger n = BigInteger.valueOf(2);
        BigInteger val;
        do {
            val = n;
            seg[tot++] = val;

            BigInteger tt = t.multiply( BigInteger.valueOf(3) );
            tt = tt.add( n.multiply( BigInteger.valueOf(4) ) );

            BigInteger nn = t.multiply( BigInteger.valueOf(2) );
            nn = nn.add( n.multiply( BigInteger.valueOf(3) ) );

            t = tt; n = nn;
        } while(val.compareTo(lim) < 0);

        t = BigInteger.valueOf(7);
        n = BigInteger.valueOf(2);
        do {
            val = n.multiply( BigInteger.valueOf(3) );
            seg[tot++] = val;

            BigInteger tt = t.multiply( BigInteger.valueOf(7) );
            tt = tt.add( n.multiply( BigInteger.valueOf(24) ) );

            BigInteger nn = t.multiply( BigInteger.valueOf(2) );
            nn = nn.add( n.multiply( BigInteger.valueOf(7) ) );

            t = tt; n = nn;
        } while(val.compareTo(lim) < 0);
    }

    public static void main(String[] args) {
        Pre();
        Scanner in = new Scanner(System.in);
        boolean fg = false;
        BigInteger ans = BigInteger.ZERO;
        BigInteger m = in.nextBigInteger();
        for(int i = 0; i < tot; ++i) {
            if(seg[i].compareTo(m) < 0) continue;
            if(!fg) {
                ans = seg[i];
                fg = true;
            }
            else if(seg[i].compareTo(ans) < 0)
                ans = seg[i];
        }
        System.out.println(ans);
        return;
    }
}
