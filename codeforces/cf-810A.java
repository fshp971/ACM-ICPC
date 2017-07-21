import java.util.*;

public class Main {
	final static int maxn = 10;
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt(), kk = sc.nextInt(), sum = 0;
		for(int i = 1; i <= n; ++i)
			sum += sc.nextInt();
		for(int i = 0; ; ++i) {
			int mn = (int)( (kk - 0.5) * (i + n) + 0.5 );
			int mx = (int)( (kk + 0.5) * (i + n) );
			if(mx == (kk + 0.5) * (i + n))
				--mx;
			if(mn > mx) continue;
			if(sum + i > mx) continue;
			if(sum + i * kk < mn) continue;
			System.out.println(i);
			break;
		}
	}
}
