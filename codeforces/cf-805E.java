import java.util.*;
import java.io.*;

public class Main {

	static int debug = 1;
	static final int maxn = (int)3e5;
	static int n, m, lim = 1;
	static ArrayList< ArrayList<Integer> > G = new ArrayList< ArrayList<Integer> >(maxn + 2);
	static int[][] Uni = new int[maxn + 2][];
	static int Col[] = new int[maxn + 2];
	static int vist[] = new int[maxn + 2];

	static private void dfs(int x, int par) {
		int pos = 1;
		for(int i = 1; i <= Uni[x][0]; ++i)
			vist[ Col[Uni[x][i]] ] = x;
		for(int i = 1; i <= Uni[x][0]; ++i) {
			if(Col[Uni[x][i]] == 0) {
				while(vist[pos] == x) ++pos;
				Col[ Uni[x][i] ] = pos;
				++pos;
			}
		}
		for(int i = 0; i < G.get(x).size(); ++i) {
			if(G.get(x).get(i) != par)
				dfs(G.get(x).get(i), x);
		}
	}

	static public void main(String[] args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader sc = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);

		n = sc.nextInt();
		m = sc.nextInt();
		for(int i = 0; i <= n; ++i) G.add(new ArrayList<Integer>());
		for(int i = 1; i <= n; ++i) {
			int si = sc.nextInt();
			Uni[i] = new int[si + 1];
			Uni[i][0] = si;
			for(int k = 1; k <= si; ++k)
				Uni[i][k] = sc.nextInt();
		}
		for(int i = 1; i < n; ++i) {
			int u = sc.nextInt(), v = sc.nextInt();
			G.get(u).add(v);
			G.get(v).add(u);
		}
		dfs(1, 0);
		for(int i = 1; i <= m; ++i) lim = Math.max(lim, Col[i]);
		out.println(lim);
		for(int i = 1; i <= m; ++i) {
			if(i > 1) out.print(" ");
			out.print(Math.max(Col[i], 1));
		}
		out.println();
		out.close();
	}

	//By Petr
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
