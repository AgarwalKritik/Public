package com.cmru.java;

// Java program to print numbers 1 to 100

public class PrintHundred {
    public void header(){
        System.out.println("-------------------------------------------------------------------------------");
        System.out.println("|                   JAVA PROGRAM BY KRITIK AGARWAL 19BBTCS067                 |");
        System.out.println("-------------------------------------------------------------------------------");
    }
    public static void main(String[] args){
        PrintHundred ph = new PrintHundred();
        ph.header();
        for(int i=1; i<=100;i++){
            System.out.println(i);
        }
    }

}
