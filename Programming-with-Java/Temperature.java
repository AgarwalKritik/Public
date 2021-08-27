package com.Kritik.java.Assignment;

public class Temperature {
    public static void main(String[] args) {
        double fahrenheit = 62.5;
        /* Convert */
        double celsius = Temperature.f2c(fahrenheit);
        System.out.println(fahrenheit + "F = " + celsius + "C");
    }

    public static double f2c(double fahr) {
        return (fahr - 32) * 5 / 9;
    }
}
