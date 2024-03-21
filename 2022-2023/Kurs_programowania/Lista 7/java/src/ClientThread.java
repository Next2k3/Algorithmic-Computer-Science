import java.io.*;
import java.net.*;

// Wątek do obsługi klienta
public class ClientThread extends Thread {
    private Socket socket;
    private long id = getId();

    public ClientThread(Socket socket) {
        this.socket = socket;
    }

    @Override
    public void run() {
        try {
            // Utworzenie strumienia wejściowego do odbierania danych od klienta
            InputStream inputStream = socket.getInputStream();
            BufferedReader input = new BufferedReader(new InputStreamReader(inputStream));

            // Utworzenie strumienia wyjściowego do wysyłania danych do klienta
            OutputStream outputStream = socket.getOutputStream();
            PrintWriter output = new PrintWriter(outputStream, true);

            // Odczytanie typu danych wysłanego przez klienta
            String type = input.readLine();

            // Obsługa drzewa binarnego w zależności od typu danych
            if (type.equals("Integer")) {
                TreeOperations<Integer> treeRequests = new TreeOperations<>(new IntegerParser(), input, output);
                treeRequests.handleRequests();
            } else if (type.equals("Double")) {
                TreeOperations<Double> treeRequests = new TreeOperations<>(new DoubleParser(), input, output);
                treeRequests.handleRequests();
            } else if (type.equals("String")) {
                TreeOperations<String> treeRequests = new TreeOperations<>(new StringParser(), input, output);
                treeRequests.handleRequests();
            }

            // Zamknięcie gniazda
            try {
                socket.close();
            } catch (final IOException ex) {
                System.out.println("Error while closing socket: " + ex.getMessage());
                ex.printStackTrace();
            }

            System.out.println("Client " + id + " disconnected");

            // Zakończenie wątku
            this.interrupt();

        } catch (final IOException ex) {
            System.out.println("Server exception: " + ex.getMessage());
            ex.printStackTrace();
        }
    }
}

