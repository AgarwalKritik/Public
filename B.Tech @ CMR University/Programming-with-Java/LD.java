package com.Kritik.java.Assignment;

public class LD {
//    public int lastDigit(int d) {
//        return Math.abs(d % 10);
//    }

    public int firstDigit(int n) {
        n = Math.abs(n);
        while(n > 9)
            n /= 10;
        return n;
    }

    public static void main(String[] args) {
        LD l = new LD();
        int a = l.firstDigit(3572);
        int b = l.firstDigit(-947);
        System.out.println("A = "+a+" B = "+b);
    }
}
