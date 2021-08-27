package com.cmru.java.lab.Lab1;

import java.util.Scanner;

public class Denomination {
    public void header(){
        System.out.println("-------------------------------------------------------------------------------");
        System.out.println("|                   JAVA PROGRAM BY KRITIK AGARWAL 19BBTCS067                 |");
        System.out.println("-------------------------------------------------------------------------------");
    }
    private void countDenom(int amnt) {
        int INR1 = 0, INR2 = 0, INR5 = 0, INR10 = 0, INR20 = 0, INR50 = 0, INR100 = 0, INR200 = 0, INR500 = 0, INR2000 = 0;
        if (amnt >= 2000) {
            INR2000 = amnt / 2000;
            amnt -= INR2000 * 2000;
        }
        if (amnt >= 500) {
            INR500 = amnt / 500;
            amnt -= INR500 * 500;
        }
        if (amnt >= 200) {
            INR200 = amnt / 200;
            amnt -= INR200 * 200;
        }
        if (amnt >= 100) {
            INR100 = amnt / 100;
            amnt -= INR100 * 100;
        }
        if (amnt >= 50) {
            INR50 = amnt / 50;
            amnt -= INR50 * 50;
        }
        if (amnt >= 20) {
            INR20 = amnt / 20;
            amnt -= INR20 * 20;
        }
        if (amnt >= 10) {
            INR10 = amnt / 10;
            amnt -= INR10 * 10;
        }
        if (amnt >= 5) {
            INR5 = amnt / 5;
            amnt -= INR5 * 5;
        }
        if (amnt >= 2) {
            INR2 = amnt / 2;
            amnt -= INR2 * 2;
        }
        if (amnt >= 1)
            INR1 = amnt;
        System.out.println("Minimum Denominations: ");
        if(INR2000!=0)
            System.out.println("INR 2000 = "+INR2000);
        if(INR500!=0)
            System.out.println("INR 500 = "+INR500);
        if(INR200!=0)
            System.out.println("INR 200 = "+INR200);
        if(INR100!=0)
            System.out.println("INR 100 = "+INR100);
        if(INR50!=0)
            System.out.println("INR 50 = "+INR50);
        if(INR20!=0)
            System.out.println("INR 20 = "+INR20);
        if(INR10!=0)
            System.out.println("INR 10 = "+INR10);
        if(INR5!=0)
            System.out.println("INR 5 = "+INR5);
        if(INR2!=0)
            System.out.println("INR 2 = "+INR2);
        if(INR1!=0)
            System.out.println("INR 1 = "+INR1);
    }
    public static void main(String[] args) {
        Denomination d = new Denomination();
        Scanner input = new Scanner(System.in);
        int n;
        do {
            d.header();
            System.out.println("Please Enter Amount in INR: ");
            int amnt = input.nextInt();
            d.countDenom(amnt);
            System.out.println("Press any number to continue or 0 to exit: ");
            n = input.nextInt();
        }while(n!=0);
    }
}
