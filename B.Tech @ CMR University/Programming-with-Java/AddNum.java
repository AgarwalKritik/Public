package com.cmru.java;

import java.util.Scanner;

// Java program to add two numbers

public class AddNum {
    public void header(){
        System.out.println("-------------------------------------------------------------------------------");
        System.out.println("|                   JAVA PROGRAM BY KRITIK AGARWAL 19BBTCS067                 |");
        System.out.println("-------------------------------------------------------------------------------");
    }
    public static void main(String[] args){
        AddNum an = new AddNum();
        an.header();
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter First Number: ");
        int x = sc.nextInt();
        System.out.println("Enter Second Number: ");
        int y = sc.nextInt();
        System.out.println("\n>>> Result: "+(x+y));
    }
}
