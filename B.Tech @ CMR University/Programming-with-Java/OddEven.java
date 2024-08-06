package com.cmru.java;

// Java program to print even and odd numbers 1 to 100

import java.util.Scanner;

public class OddEven {
    public void header(){
        System.out.println("-------------------------------------------------------------------------------");
        System.out.println("|                   JAVA PROGRAM BY KRITIK AGARWAL 19BBTCS067                 |");
        System.out.println("-------------------------------------------------------------------------------");
    }
    public void odd(){
        System.out.println("---- ODD NUMBERS ----");
        for(int i=1; i<=100; i++){
            if(i%2!=0)
                System.out.println(i);
        }
    }
    public void even(){
        System.out.println("---- EVEN NUMBERS ----");
        for(int i=1; i<=100; i++){
            if(i%2==0)
                System.out.println(i);
        }
    }
    public static void main(String[] args){
        OddEven oe = new OddEven();
        Scanner sc = new Scanner(System.in);
        oe.header();
        System.out.println("1. Even Numbers\n2. Odd Numbers\nSelect Your Choice: ");
        int choice = sc.nextInt();
        switch (choice) {
            case 1 -> oe.even();
            case 2 -> oe.odd();
            default -> System.out.println("\nWrong Choice!!");
        }
    }
}
