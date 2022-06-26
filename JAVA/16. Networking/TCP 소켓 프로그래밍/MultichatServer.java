package com.company;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Iterator;
import java.util.concurrent.ConcurrentHashMap;

public class MultichatServer {
    //HashMap clients;
    ConcurrentHashMap clients;
    MultichatServer() {
        clients = new ConcurrentHashMap();
        //clients = new HashMap();
        //Collections.synchronizedMap(clients);
    }

    public void start() {
        ServerSocket serverSocket = null;
        Socket socket = null;

        try {
            serverSocket = new ServerSocket(7777);
            System.out.println("server is ready");

            while (true) {
                socket = serverSocket.accept();
                System.out.println("[" + socket.getInetAddress() + ":" + socket.getPort() + " is connected.");
                ServerReceiver thread = new ServerReceiver(socket);
                thread.start();
            }
        } catch (Exception e) {e.printStackTrace();}
    }

    void sendToAll(String msg) {
        Iterator itr = clients.keySet().iterator();
        while (itr.hasNext()) {
            try {
                DataOutputStream outputStream = (DataOutputStream) clients.get(itr.next());
                outputStream.writeUTF(msg);
            } catch (IOException ie) {ie.printStackTrace();}
        }
    }

    public static void main(String[] args) {
        new MultichatServer().start();
    }

    class ServerReceiver extends Thread {
        Socket socket;
        DataInputStream inputStream;
        DataOutputStream outputStream;

        ServerReceiver(Socket socket) {
            this.socket = socket;
            try {
                inputStream = new DataInputStream(socket.getInputStream());
                outputStream = new DataOutputStream(socket.getOutputStream());
            } catch (IOException ie) {
                ie.printStackTrace();
            }
        }

        public void run() {
            String name = "";

            try {
                // 시작할 때 누구 입장하면 이거 출력하고 아래서 while로 계속 입력 받아.
                name = inputStream.readUTF();
                sendToAll("#" + name + " has entered.");

                clients.put(name, outputStream);
                // clients.size();
                while (inputStream != null) {
                    sendToAll(inputStream.readUTF());
                }
            } catch (IOException ie) {ie.printStackTrace();}
            finally {
                sendToAll("#" + name + " has left. [" + socket.getInetAddress() + ":" + socket.getPort() + "]");
                clients.remove(name);
            }
        }
    }
}
