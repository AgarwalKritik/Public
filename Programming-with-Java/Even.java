package com.cmru.java;

// Java program to print even numbers 1 to 100

public class Even {
    public void header(){
        System.out.println("-------------------------------------------------------------------------------");
        System.out.println("|                   JAVA PROGRAM BY KRITIK AGARWAL 19BBTCS067                 |");
        System.out.println("-------------------------------------------------------------------------------");
    }
    public static void main(String[] args){
        Even e = new Even();
        e.header();
        for(int i=1; i<=100; i++){
            if(i%2==0)
                System.out.println(i);
        }
    }
}
