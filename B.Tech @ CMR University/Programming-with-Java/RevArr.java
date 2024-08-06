package com.cmru.java;

import java.util.Scanner;

// Java Program to print the elements of an array in reverse order

public class RevArr {
    public void header(){
        System.out.println("-------------------------------------------------------------------------------");
        System.out.println("|                   JAVA PROGRAM BY KRITIK AGARWAL 19BBTCS067                 |");
        System.out.println("-------------------------------------------------------------------------------");
    }
    public static void main(String[] args){
        RevArr ra = new RevArr();
        ra.header();
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter Array Size: ");
        int size = sc.nextInt();
        char[] arr = new char[size];
        System.out.println("Enter Array Elements: ");
        for(int i=0; i<arr.length; i++)
            arr[i] = sc.next().charAt(0);
        System.out.println("Reversed Array: ");
        for(int j= arr.length-1;j>=0;j--)
            System.out.print(arr[j]);

    }
}
