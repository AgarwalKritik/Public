package com.cmru.java;

import java.util.Scanner;

// Java program to print Name and Reg Num

public class NameReg {
    public void header(){
        System.out.println("-------------------------------------------------------------------------------");
        System.out.println("|                   JAVA PROGRAM BY KRITIK AGARWAL 19BBTCS067                 |");
        System.out.println("-------------------------------------------------------------------------------");
    }
    public static void main(String[] args){
        NameReg nr = new NameReg();
        nr.header();
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter Your Name: ");
        String name = sc.nextLine();
        System.out.println("Enter Your Reg Number: ");
        String regNo = sc.nextLine();
        System.out.println("\nName: "+name);
        System.out.println("Reg. No.: "+regNo);
    }
}
