// Author: Kritik Agarwal <https://github.com/Kritik007>

// Implementation of The Signature Schemes - Digital Signature Standard in JAVA

import java.io.UnsupportedEncodingException;
import java.util.*;
import java.security.*;

public class DigitalSignature {
    public static void main(String[] args) {
        //Input from User
        heading();
        Scanner scanner = new Scanner(System.in);
        System.out.println("-> Enter some text: ");
        String msg = scanner.nextLine();

        //Creating KeyPair generator object
        KeyPairGenerator keyPairGen = null;
        try {
            keyPairGen = KeyPairGenerator.getInstance("DSA");
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }

        //Initializing the key pair generator
        keyPairGen.initialize(2048);

        //Generate the pair of keys
        KeyPair pair = keyPairGen.generateKeyPair();

        //Getting the private key from the key pair
        PrivateKey privKey = pair.getPrivate();

        //Creating a Signature object
        Signature sign = null;
        try {
            sign = Signature.getInstance("SHA256withDSA");
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }

        //Initialize the signature
        try {
            sign.initSign(privKey);
        } catch (InvalidKeyException e) {
            throw new RuntimeException(e);
        }
        byte[] bytes = "msg".getBytes();

        //Adding data to the signature
        try {
            sign.update(bytes);
        } catch (SignatureException e) {
            throw new RuntimeException(e);
        }

        //Calculating the signature
        byte[] signature = new byte[0];
        try {
            signature = sign.sign();
        } catch (SignatureException e) {
            throw new RuntimeException(e);
        }

        //Printing the signature
        try {
            System.out.println("-> Digital signature for given text: "+new String(signature, "UTF8"));
        } catch (UnsupportedEncodingException e) {
            throw new RuntimeException(e);
        }

        //Initializing the signature
        try {
            sign.initVerify(pair.getPublic());
        } catch (InvalidKeyException e) {
            throw new RuntimeException(e);
        }
        try {
            sign.update(bytes);
        } catch (SignatureException e) {
            throw new RuntimeException(e);
        }

        //Verifying the signature
        boolean bool = false;
        try {
            bool = sign.verify(signature);
        } catch (SignatureException e) {
            throw new RuntimeException(e);
        }

        if(bool) {
            System.out.println("\n>>> Signature verified!!\n");
        } else {
            System.out.println("\n>>> Signature failed!!\n");
        }
    }

    public static void heading()
    {
        System.out.println("-------------------------------------------------------------------------------");
        System.out.println("|                             Digital Signature Standard                      |");
        System.out.println("|                             KRITIK AGARWAL 19BBTCS067                       |");
        System.out.println("-------------------------------------------------------------------------------");
    }
}