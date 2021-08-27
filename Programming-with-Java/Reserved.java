package com.cmru.java.lab.Assignment;

import java.util.Scanner;

abstract class Reservation{
    abstract void Reserve();
}

class ReserveTrain extends Reservation{
    public void Reserve(){
        System.out.println(">>> Train is reserved");
    }
}

class ReserveBus extends Reservation{
    public void Reserve() {
        System.out.println(">>> Bus is reserved");
    }
}

public class Reserved {
    public static void main(String[] args) {
        Reservation rb = new ReserveBus();
        Reservation rt = new ReserveTrain();
        Scanner sc = new Scanner(System.in);
        System.out.print("\nWhat do you want to reserve? 1. Bus or 2. Train?\n>>>");
        int n = sc.nextInt();
        switch(n){
            case 1 -> rb.Reserve();
            case 2 -> rt.Reserve();
            default -> System.out.println("Wrong Input");
        }
    }
}

