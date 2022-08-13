import java.io.*;

public class App {
    public static void main(String[] args) {
        try {
            InputStream in = new LowerCaseInputStream(
                new BufferedInputStream(
                    new FileInputStream("test.txt")
                )
            );
            int c;
            while ((c = in.read()) >= 0) {
                System.out.print((char)c);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}