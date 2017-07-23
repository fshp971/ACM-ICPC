import java.util.*;

public class Main {
	static final long md = (long)(1E9 + 7);
	static final int maxn = (int)1e6;
	static final long[] two = new long[maxn + 2];
	static public void main(String[] args) {
		two[0] = 1;
		for(int i = 1; i <= maxn; ++i)
			two[i] = two[i-1] * 2 % md;
		Scanner sc = new Scanner(System.in);
		String str = sc.next();
		int len = str.length(), cont = 0;
		long ans = 0;
		for(int i = 0; i < len; ++i) {
			if(str.charAt(i) == 'a')
				++cont;
			else ans = (ans + two[cont] - 1 + md) % md;
		}
		System.out.println(ans);
	}
}
