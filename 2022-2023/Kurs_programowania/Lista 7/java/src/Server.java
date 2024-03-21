import java.io.*;
import java.net.*;

public class Server {

    public static void main(String[] args) {

        try (ServerSocket serverSocket = new ServerSocket(4444)) {
            // Tworzenie gniazda serwerowego na porcie 4444
            System.out.println("Server is listening on port 4444");

            while (true) {
                // Akceptowanie połączenia od klienta
                Socket socket = serverSocket.accept();
                System.out.println("New client connected");

                // Tworzenie i uruchamianie nowego wątku obsługującego klienta
                new ClientThread(socket).start();
            }

        } catch (IOException ex) {
            // Obsługa wyjątku w przypadku błędu serwera
            System.out.println("Server exception: " + ex.getMessage());
            ex.printStackTrace();
        }
    }
}
