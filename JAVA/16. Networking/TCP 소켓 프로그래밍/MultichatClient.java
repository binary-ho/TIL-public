package com.company;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ConnectException;
import java.net.Socket;
import java.util.Scanner;

public class MultichatClient {

    public static void main(String[] args) {
        if(args.length != 1) {
            System.out.println("USAGE: java MultichatClient name");
            System.exit(0);
        }

        try {
            String serverIp = "127.0.0.1";
            Socket socket = new Socket(serverIp, 7777);
            System.out.println("server is ready");
            Thread sender = new Thread(new ClientSender(socket, args[0]));
            Thread receiver = new Thread(new ClientReceiver(socket));

            sender.start();
            receiver.start();
        } catch (ConnectException ce) {ce.printStackTrace();}
        catch (Exception e) {}
    }

    static class ClientSender extends Thread {
        Socket socket;
        DataOutputStream outputStream;
        String name;

        ClientSender(Socket socket, String name) {
            this.socket = socket;
            try {
                outputStream = new DataOutputStream(socket.getOutputStream());
                this.name = name;
            } catch (Exception e) {}
        }

        public void run() {
            Scanner scanner = new Scanner(System.in);
            try {
                if(outputStream != null) {
                    outputStream.writeUTF(name);
                }
                while (outputStream != null) {
                    outputStream.writeUTF("[" + name + "]" + scanner.nextLine());
                }
            } catch (IOException ie) {}
        }
    }

    static class ClientReceiver extends Thread {
        Socket socket;
        DataInputStream inputStream;

        ClientReceiver(Socket socket) {
            this.socket = socket;
            try {
                inputStream = new DataInputStream(socket.getInputStream());
            } catch (IOException ie) {}
        }

        public void run() {
            while (inputStream != null) {
                try {
                    System.out.println(inputStream.readUTF());
                } catch (IOException e) {}
            }
        }
    }
}
