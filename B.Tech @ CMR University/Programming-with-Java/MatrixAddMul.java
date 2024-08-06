package com.Kritik.java.Assignment;

import java.util.Scanner;

public class MatrixAddMul {
    public int[] readRowCol() {
        Scanner in = new Scanner(System.in);
        int[] rc = new int[2];
        rc[0] = in.nextInt();
        rc[1] = in.nextInt();
        return rc;
    }

    public int[][] readMat(int[][] reads, int col, int row) {
        Scanner in = new Scanner(System.in);
        for (int c = 0; c < col; c++)
            for (int d = 0; d < row; d++)
                reads[c][d] = in.nextInt();
        return reads;
    }

    public void printMat(int[][] prints, int m, int p) {
        for (int c = 0; c < m; c++) {
            for (int d = 0; d < p; d++)
                System.out.print(prints[c][d] + "\t");
            System.out.println();
        }
    }

    public static void main(String[] args) {
        int c, d, m, n, p, q, ch;
        MatrixAddMul im = new MatrixAddMul();
        Scanner in = new Scanner(System.in);
        System.out.println(">>> Enter the number of rows and columns of first matrix");
        int[] row_col = im.readRowCol();
        m = row_col[0];
        n = row_col[1];
        int[][] first = new int[m][n];
        System.out.println(">>> Enter elements of first matrix");
        first = im.readMat(first, m, n);
        System.out.println(">>> Enter the number of rows and columns of second matrix");
        row_col = im.readRowCol();
        p = row_col[0];
        q = row_col[1];
        int[][] second = new int[p][q];
        System.out.println(">>> Enter elements of second matrix");
        second = im.readMat(second, p, q);
        System.out.println(">>> 1.Addition \n>>> 2.Multiplication ");
        System.out.print(">>> Enter your choice : ");
        ch = in.nextInt();
        switch (ch) {
            case 1 -> {
                int[][] add = new int[10][10];
                if ((m == p) && (n == q)) {
                    System.out.println("\n>>> Addition is possible ");
                    for (c = 0; c < m; c++)
                        for (d = 0; d < p; d++)
                            add[c][d] = first[c][d] + second[c][d];
                    im.printMat(add, m, p);
                } else
                    System.out.println("\n>>> Addition is not possible:-");
            }
            case 2 -> {
                int[][] multiply = new int[10][10];
                if (n == p) {
                    System.out.println(">>> Multiplication is possible ");
                    int sum = 0;
                    for (c = 0; c < m; c++) {
                        for (d = 0; d < q; d++) {
                            for (int k = 0; k < p; k++)
                                sum += first[c][k] * second[k][d];
                            multiply[c][d] = sum;
                            sum = 0;
                        }
                    }
                    System.out.println(">>> Product of the matrices:");
                    im.printMat(multiply, m, q);
                } else
                    System.out.println(">>> Multiplication is not possible ");
            }
            default -> System.out.println(">>> Invalid choice ");
        }

    }
}
