import java.io.*;
import java.net.Socket;
import java.util.Objects;
import java.util.Scanner;

public class cClient
{


    public static void main(String[] args) {

        Socket s;
        BufferedReader br;
        BufferedWriter bw;
        PrintWriter pw;
        Scanner sc = new Scanner(System.in);
        String status, finalst, name;
        int x;
        int PORT = 8884;
        int ADDRESE_TARGET = "localhost" // or 127.0.0.1

        try {
            s = new Socket(ADDRESE_TARGET, PORT);
            br = new BufferedReader(new InputStreamReader(s.getInputStream()));
            bw = new BufferedWriter(new OutputStreamWriter(s.getOutputStream()));
            pw = new PrintWriter(s.getOutputStream(),true);

            System.out.println("What is your Name : ");
            name = sc.nextLine();
            bw.write(name);
            bw.flush();

            System.out.println(br.readLine());
            System.out.println(br.readLine());


            do {
                x = sc.nextInt();
                String l = Integer.toString(x);
                bw.write(l);
                bw.flush();
                System.out.println(br.readLine());

                status = br.readLine();

                finalst = br.readLine();


            }while(!status.equals("good") && !finalst.equals("over"));

        }catch (IOException e){}

    }
}
