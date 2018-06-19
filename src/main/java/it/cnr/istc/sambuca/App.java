package it.cnr.istc.sambuca;

import java.io.IOException;

public class App {

    public static void main(String[] args) {
        try {
            SaMBuCA smb = new SaMBuCA(args[0], args[1]);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
