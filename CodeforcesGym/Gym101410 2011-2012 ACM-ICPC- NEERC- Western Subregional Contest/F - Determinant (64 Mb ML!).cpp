import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	static int n;
	static BigInteger[][] mmp = new BigInteger[35][35];
	static BigInteger zero = new BigInteger("0"), one = new BigInteger("1");
	static BigInteger dest, ans = zero, det;
	static BigInteger[][] A = new BigInteger[35][80];

	static void Gauss() {
		BigInteger g, tmp1, tmp2;
		int fg = 1;
		BigInteger delta = one;
		for(int i = 0; i < n; ++i) {
			for(int k = 0; k < n; ++k)
				A[i][k] = mmp[i][k];
		}
		for(int i = 0; i < n; ++i)
			for(int k = 0; k < n; ++k)
				A[i][k + n] = (k == i) ? one : zero;

		for(int i = 0; i < n; ++i) {
			int r = i;
			for(int j = i; j < n; ++j)
				if(A[j][i].compareTo(zero) != 0) {
					r = j; break;
				}
			if(i != r) {
				fg = -fg;
				for(int j = 0; j < n * 2; ++j) {
					tmp1 = A[i][j]; A[i][j] = A[r][j]; A[r][j] = tmp1;
				}
			}
			for(int j = i + 1; j < n; ++j) {
				if(A[j][i].compareTo(zero) == 0) continue;
				g = A[i][i].gcd(A[j][i]);
				tmp1 = A[i][i].divide(g);
				tmp2 = A[j][i].divide(g);
				delta = delta.multiply(tmp1);
				for(int k = i; k < n * 2; ++k)
					A[j][k] = ( A[j][k].multiply(tmp1) ).subtract( A[i][k].multiply(tmp2) );
			}
		}
		for(int i = n - 1; i >= 0; --i) {
			for(int j = 0; j < i; ++j) {
				if(A[j][i].compareTo(zero) == 0) continue;
				g = A[i][i].gcd(A[j][i]);
				tmp1 = A[i][i].divide(g);
				tmp2 = A[j][i].divide(g);
				delta = delta.multiply(tmp1);
				for(int k = 0; k < n * 2; ++k)
					A[j][k] = ( A[j][k].multiply(tmp1) ).subtract( A[i][k].multiply(tmp2) );
			}
		}

		det = one;
		for(int i = 0; i < n; ++i)
			det = det.multiply(A[i][i]);
		if(fg == -1) delta = zero.subtract(delta);
		det = det.divide(delta);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				A[i][j + n] = ( A[i][j + n].multiply(det) ).divide(A[i][i]);
	}

	public static void main(String[] args) throws FileNotFoundException {
		Scanner in = new Scanner(new File("det.in"));
		PrintWriter out = new PrintWriter("det.out");
		n = in.nextInt();
		String str;
		for(int i = 0; i < n; ++i) {
			for(int k = 0; k < n; ++k) {
				str = in.next();
				mmp[i][k] = new BigInteger(str);
			}
		}
		Gauss();
		str = in.next();
		dest = new BigInteger(str);
		BigInteger tmp;
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				tmp = zero;
				for(int k = 0; k < n; ++k)
					if(k != j)
						tmp = tmp.add( mmp[i][k].multiply(A[k][i + n]) );
				tmp = dest.subtract(tmp);
				if(A[j][i + n].compareTo(zero) == 0) {
					if(tmp.compareTo(zero) != 0)
						continue;
				}
				else {
					ans = tmp.divide(A[j][i + n]);
					if(ans.multiply(A[j][i + n]).compareTo(tmp) != 0)
						continue;
				}
				out.println( (i+1) + " " + (j+1) + " " + ans);
				out.flush();
				out.close();
				return;
			}
		}
		out.print("-1\n");
		out.flush();
		out.close();
		return;
	}
}
