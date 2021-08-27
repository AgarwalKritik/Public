package com.Kritik.java.Assignment;

public class LoopCtrl {
    public static void main(String[] args) {
               int[] Arr = {4,5,7,8};
               int sum=0;
               for(int i : Arr){
                    sum+=i;
               }
               double avg = sum / Arr.length;
                System.out.println(avg);
    }
}
