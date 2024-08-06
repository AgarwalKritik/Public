package com.cmru.java.lab.Lab3;

public class Wrapper {
    public void header(){
        System.out.println("-------------------------------------------------------------------------------");
        System.out.println("|                   JAVA PROGRAM BY KRITIK AGARWAL 19BBTCS067                 |");
        System.out.println("-------------------------------------------------------------------------------");
    }
    public static void main(String[] args) {
        Wrapper w = new Wrapper();
        byte b = 5;
        short s = 10;
        int i = 15;
        long l = 20;
        float f = 25.0F;
        double d = 30.0D;
        char c = 'k';
        boolean b2 = true;
        Byte bobj = b;
        Short sobj = s;
        Integer iobj = i;
        Long lobj = l;
        Float fobj = f;
        Double dobj = d;
        Character chobj = c;
        Boolean boolobj = b2;
        byte bvalue = bobj;
        short svalue = sobj;
        int ivalue = iobj;
        long lvalue = lobj;
        float fvalue = fobj;
        double dvalue = dobj;
        char chvalue = chobj;
        boolean boolvalue = boolobj;
        w.header();
        System.out.println("------------------------");
        System.out.println("      Object values     ");
        System.out.println("------------------------");
        System.out.println(">>> Byte: " + bobj);
        System.out.println(">>> Short: " + sobj);
        System.out.println(">>> Integer: " + iobj);
        System.out.println(">>> Long: " + lobj);
        System.out.println(">>> Float: " + fobj);
        System.out.println(">>> Double: " + dobj);
        System.out.println(">>> Character: " + chobj);
        System.out.println(">>> Boolean: " + boolobj);

        System.out.println("\n------------------------");
        System.out.println("    Primitive Values    ");
        System.out.println("------------------------");
        System.out.println(">>> byte: " + bvalue);
        System.out.println(">>> short: " + svalue);
        System.out.println(">>> int: " + ivalue);
        System.out.println(">>> long: " + lvalue);
        System.out.println(">>> float: " + fvalue);
        System.out.println(">>> double: " + dvalue);
        System.out.println(">>> char: " + chvalue);
        System.out.println(">>> boolean: " + boolvalue);
    }
}
