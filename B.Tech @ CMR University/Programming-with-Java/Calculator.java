package com.cmru.java;

import java.util.Scanner;

// Java program to add two numbers

public class Calculator {
    public void header(){
        System.out.println("-------------------------------------------------------------------------------");
        System.out.println("|                   JAVA PROGRAM BY KRITIK AGARWAL 19BBTCS067                 |");
        System.out.println("-------------------------------------------------------------------------------");
    }
    public void calculator(){
        Scanner sc = new Scanner(System.in);
        System.out.println("1. Addition\n2. Subtraction\n3. Multiply\n4. Divide");
        System.out.println("Enter Your Choice: ");
        int n = sc.nextInt();
        System.out.println("Enter First Number: ");
        int x = sc.nextInt();
        System.out.println("Enter Second Number: ");
        int y = sc.nextInt();
        switch (n) {
            case 1 -> System.out.println("\n>>> Result: " + (x + y));
            case 2 -> System.out.println("\n>>> Result: " + (x - y));
            case 3 -> System.out.println("\n>>> Result: " + (x * y));
            case 4 -> System.out.println("\n>>> Result: " + (x / y));
            default -> System.out.println("\nWrong Choice!!");
        }
    }
    public static void main(String[] args) {
        Calculator calc = new Calculator();
        Scanner sc = new Scanner(System.in);
        calc.header();
        calc.calculator();
        int ans = 1;
        do {
            System.out.println("\nEnter Any Number to Continue\nEnter 0 to Exit ");
            ans = sc.nextInt();
            calc.calculator();
        }while (ans !=0);
    }
}
