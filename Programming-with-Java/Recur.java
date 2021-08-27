package com.cmru.java.lab.Assignment;

import java.util.Scanner;

public class Recur {
    public static int Num, n = 1;

    public static void recurPrint(int n) {
        if (n < Num) {
            System.out.println(n++);
            //n++;
            recurPrint(n);
        } else
            return;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("\n>>> Enter a number: ");
        Num = sc.nextInt();
        System.out.println();
        Recur.recurPrint(n);
    }
}