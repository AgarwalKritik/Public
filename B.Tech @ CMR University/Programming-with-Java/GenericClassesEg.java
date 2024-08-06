package com.cmru.java.lab.Lab6;

import java.util.*;

public class GenericClassesEg {
    public static void main(String[] args) {
        //a. Type Safety && Compile Time Checking
        //GENERIC
        ArrayList<String> al = new ArrayList<>();
        al.add("CMRIT");
        al.add("CMRU");
        //al.add(20); //CompileTimeError: 'add(java.lang.String)' in 'java.util.ArrayList' cannot be applied to '(int)'
        al.add("VTU");
        al.add("PESIT");
        String k = al.get(1);
        System.out.println("Value: "+k);

        //b. Type Casting
        //NON-GENERIC
        ArrayList il = new ArrayList<>();
        il.add(21);
        il.add("22");
        int l = (int) il.get(0);
        System.out.println("Value: "+l);
    }
}
