package com.Kritik.java.Assignment;

import java.util.Scanner;

interface Interest {
    void simpleInterest(double p, double t);
    void compInterest(double p, double t, int n);
    double rate = 25;
}

class CalcInterest implements Interest {
    public void simpleInterest(double p, double t) {
        double si = (p * Interest.rate * t) / 100;
        System.out.println("\n>>> Simple Interest is : ₹" + String.format("%.2f",si)+"/-");
        double amount = p + si;
        System.out.println(">>> Total Amount with Simple Interest : ₹" + String.format("%.2f",amount)+"/-");
    }

    public void compInterest(double p, double t, int n) {
        double amount = p * Math.pow(1 + ((Interest.rate / 100) / n), n * t);
        double ci = amount - p;
        System.out.println("\n>>> Compound Interest is : ₹" + String.format("%.2f",ci)+"/-");
        System.out.println(">>> Total Amount with Compound Interest : ₹" + String.format("%.2f",amount)+"/-");
    }
}

public class SCInterest{
    public static void main(String[] args) {
        Interest i = new CalcInterest();
        Scanner scan = new Scanner(System.in);
        System.out.print("\n>>> Enter Initial Deposit Amount : ₹");
        double ida = scan.nextDouble();
        System.out.print("\n>>> Enter Time Period (in years) : ");
        double time = scan.nextDouble();
        System.out.print("\n>>> Enter Number of Times the interest has to be compounded : ");
        int n = scan.nextInt(); // n is the number of times that interest is compounded per unit t
        i.simpleInterest(ida,time);
        i.compInterest(ida,time,n);
        System.out.println("\n>>> RATE OF INTEREST is : "+String.format("%.0f",Interest.rate)+"%");
    }
}
