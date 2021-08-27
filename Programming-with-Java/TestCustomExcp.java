package com.cmru.java.lab.Lab5;

import java.util.Scanner;

public class TestCustomExcp {
	public void header(){
        System.out.println("-------------------------------------------------------------------------------");
        System.out.println("|                   JAVA PROGRAM BY KRITIK AGARWAL 19BBTCS067                 |");
        System.out.println("-------------------------------------------------------------------------------");
    }
	static void validate(int age) throws InvAgeExcp{
		if (age<18)
			throw new InvAgeExcp("Minor!! Not a valid age to vote.");
		else
			System.out.println("Welcome to Vote");
	}
	public static void main(String[] args) {
		TestCustomExcp t = new TestCustomExcp();
		Scanner sc = new Scanner(System.in);
		t.header();
		System.out.println(">> Enter your age: ");
        int a = sc.nextInt();
		try {
			validate(a);
		} catch(Exception m) {
			System.out.println("Exception thrown: " + m);
		}
		System.out.println("Completing the execution...");
	}
}
