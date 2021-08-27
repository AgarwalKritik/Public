package com.cmru.java.lab.Lab4;

import java.util.Scanner;

public class ExceptionHandling {
    public void header(){
        System.out.println("-------------------------------------------------------------------------------");
        System.out.println("|                   JAVA PROGRAM BY KRITIK AGARWAL 19BBTCS067                 |");
        System.out.println("-------------------------------------------------------------------------------");
    }
    public void throwsEg(int b, int c)throws ArithmeticException, ArrayIndexOutOfBoundsException{
        if (b==0){
            throw new ArithmeticException("Division by Zero is not possible.");
        }
        if (c >= 4){
            throw new ArrayIndexOutOfBoundsException("Array Index must be between 0-3.");
        }
    }
    public void divideException(int a, int b, int c){
            int[] array = new int[4];
            array[c] = a/b;
            System.out.println(array[c]);
    }
    public static void main(String[] args) {
        ExceptionHandling eh = new ExceptionHandling();
        Scanner sc = new Scanner(System.in);
        eh.header();
        System.out.println(">> Enter two numbers ");
        int a = sc.nextInt();
        int b = sc.nextInt();
        System.out.print(">> Enter array index: ");
        int c = sc.nextInt();
        try {
            eh.throwsEg(b,c);
            eh.divideException(a,b,c);
        } catch (Exception e) {
            System.out.println("\n!! There is an Exception!! --> "+e.getMessage());
            try {
                if (e.getMessage()!="Array Index must be between 0-3."){
                    if(c>=4){
                        throw new ArrayIndexOutOfBoundsException("Array Index must be between 0-3.");
                    }
                }
            } catch (Exception en){
                System.out.println("!! There is another Exception!! --> "+en.getMessage());
            }
        }
        finally{
            System.out.println("\n>>> Program Execution Completed, Exception Handled <<<");
        }
    }
}
