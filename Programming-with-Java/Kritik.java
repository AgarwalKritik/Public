package com.cmru.java.lab.Assignment;

import java.util.Scanner;

abstract class Message{
    abstract void playMessage();
}

class TextMessage extends Message{
    public void playMessage(){
        System.out.println("\n>>> This is a Text Message <<<");
    }
}

class VoiceMessage extends Message{
    public void playMessage(){
        System.out.println("\n>>> This is a Voice Message <<<");
    }
}
class FaxMessage extends Message{
    public void playMessage(){
        System.out.println("\n>>> This is a Fax Message <<<");
    }
}

public class Kritik {
    public static void main(String[] args) {
        Message txt = new TextMessage();
        Message voice = new VoiceMessage();
        Message fax = new FaxMessage();
        Scanner scan = new Scanner(System.in);
        System.out.println("\n 1. Text Message\n 2. Voice Message\n 3. Fax Message");
        System.out.print("\n>>> Enter your choice: ");
        int ch = scan.nextInt();
        switch(ch) {
            case 1 -> txt.playMessage();
            case 2 -> voice.playMessage();
            case 3 -> fax.playMessage();
            default -> System.out.println("\n>>> Invalid Choice.");
        }
    }
}
