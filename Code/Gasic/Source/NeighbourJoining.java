import java.util.Scanner;

public class NeighbourJoining {

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int numberOfNodes = scanner.nextInt();
    int maxNumberOfNodes = 2 * numberOfNodes - 2;

    boolean[] active = new boolean[maxNumberOfNodes];
    double[][] d = new double[maxNumberOfNodes][maxNumberOfNodes];
    for (int node = 0; node < numberOfNodes; ++node) {
      active[node] = true;
      d[node][node] = 0;
    }
    for (int edge = 0; edge < numberOfNodes * (numberOfNodes - 1) / 2; ++edge) {
      int a = scanner.nextInt();
      int b = scanner.nextInt();
      d[a][b] = scanner.nextDouble();
      d[b][a] = d[a][b];
    }
    double[][] q = new double[maxNumberOfNodes][maxNumberOfNodes];
    for (int iteration = 0; iteration < numberOfNodes - 3; ++iteration) {
      double[] sum = new double[maxNumberOfNodes];
      for (int a = 0; a < maxNumberOfNodes; ++a) {
        if (!active[a]) continue;
        sum[a] = 0;
        for (int b = 0; b < maxNumberOfNodes; ++b) {
          if (!active[b]) continue;
          sum[a] += d[a][b];
        }
      }
      double minQ = Double.MAX_VALUE;
      int minA = 0;
      int minB = 0;
      for (int a = 0; a < maxNumberOfNodes; ++a) {
        if (!active[a]) continue;
        for (int b = 0; b < a; ++b) {
          if (!active[b]) continue;
          q[a][b] = (numberOfNodes - iteration - 2) * d[a][b] - sum[a] - sum[b];
          if (q[a][b] < minQ) {
            minQ = q[a][b];
            minA = a;
            minB = b;
          }
        }
      }
      int a = minA;
      int b = minB;
      int c = numberOfNodes + iteration;
      d[a][c] = 0.5 * d[a][b]  + 0.5 / (numberOfNodes - iteration - 2) * (sum[a] - sum[b]);
      d[c][a] = d[a][c];
      d[b][c] = d[a][b] - d[a][c];
      d[c][b] = d[b][c];
      active[a] = false;
      active[b] = false;
      active[c] = true;
      for (int node = 0; node < maxNumberOfNodes; ++node) {
        if (!active[node]) continue;
        d[c][node] = 0.5 * (d[a][node] + d[b][node] - d[a][b]);
        d[node][c] = d[c][node];
      }
      System.out.format("%d %d %f\n", a, c, d[a][c]);
      System.out.format("%d %d %f\n", b, c, d[b][c]);
    }
    int[] last = new int[3];
    int found = 0;
    for (int node = 0; node < maxNumberOfNodes; ++node) {
      if (active[node]) {
        last[found] = node;
        ++found;
      }
    }
    int c = maxNumberOfNodes - 1;
    for (int i = 0; i < 3; ++i) {
      int a = last[i];
      d[a][c] = 0;
      for (int j = 0; j < 3; ++j) {
        if (i == j) continue;
        d[a][c] += d[a][last[j]];
      }
      for (int j = 0; j < 3; ++j) {
        for (int k = 0; k < j; ++k) {
          if (j == i || k == i) continue;
          d[a][c] -= d[last[j]][last[k]];
          break;
        }
      }
      d[a][c] /= 2.0;
      System.out.format("%d %d %f\n", a, c, d[a][c]);
    }
  }
}
