package com.company;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class TcpIpServerSeparate {
    public static void main(String args[]) {
        ServerSocket serverSocket = null;
        Socket socket = null;

        try {
            serverSocket = new ServerSocket(7777);
            System.out.println("server is ready");

            socket = serverSocket.accept();

            Sender sender = new Sender(socket);
            Receiver receiver = new Receiver(socket);

            sender.start();
            receiver.start();
        } catch (Exception e) {e.printStackTrace();}
    }
}

class Sender extends Thread {
    Socket socket;
    DataOutputStream dataOutputStream;
    String name;

    Sender(Socket socket) {
        this.socket = socket;
        try {
            dataOutputStream = new DataOutputStream(socket.getOutputStream());
            name = "[" + socket.getInetAddress() + ":" + socket.getPort() + "] ";
        } catch (Exception e) {}
    }

    public void run() {
        Scanner scanner = new Scanner(System.in);
        while(dataOutputStream != null) {
            try {
                dataOutputStream.writeUTF(name + scanner.nextLine());
            } catch (IOException e) {}
        }
    }
}

class Receiver extends Thread {
    Socket socket;
    DataInputStream dataInputStream;

    Receiver(Socket socket) {
        this.socket = socket;
        try {
            dataInputStream = new DataInputStream(socket.getInputStream());
        } catch (IOException e) {}
    }

    public void run() {
        while (dataInputStream != null) {
            try {
                System.out.println(dataInputStream.readUTF());
            } catch (IOException e) {}
        }
    }
}
