import java.util.*;

public class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		StringBuilder str = new StringBuilder("");
		for(int i = 0; i < n; ++i) {
			if(i % 4 == 0 || i % 4 == 1)
				str = str.append('a');
			else str = str.append('b');
		}
		System.out.println(str);
	}
}
