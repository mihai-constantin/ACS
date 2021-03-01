import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

public class Main {

    public static String DATA = "_data.txt";
    public static String ANSWER = "_answer.txt";

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java Main <test_case> <number_of_hashes> <output_case>. Example: java ../test_cases/test01 50000 ../test_cases/test01");
            System.exit(1);
        }

        String inputFile = args[0];
        Integer numberOfHashes = Integer.parseInt(args[1]);

        Path input = Paths.get(inputFile + DATA);

        try (Stream<String> lines = Files.lines(input)) {
            if (args.length == 3) {
                Path output = Paths.get(args[2] + ANSWER);
                List<String> hashed = new ArrayList<>();
                lines.forEach(s -> hashed.add(encryptMultipleTimes(s, numberOfHashes)));
                Files.write(output, hashed, Charset.forName("UTF-8"));
            } else {
                lines.forEach(s -> System.out.println(s + " --> " + encryptMultipleTimes(s, numberOfHashes)));
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    private static String encryptMultipleTimes(String input, Integer count) {
        String hashed = input;
        for (int i = 0; i < count; ++i) {
            hashed = encryptThisString(hashed);
        }

        return hashed;
    }

    private static String encryptThisString(String input) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] messageDigest = md.digest(input.getBytes(StandardCharsets.UTF_8));
            
            // convert to string
            StringBuffer hexString = new StringBuffer();
            for (int i = 0; i < messageDigest.length; i++) {
            String hex = Integer.toHexString(0xff & messageDigest[i]);
            if(hex.length() == 1) hexString.append('0');
                hexString.append(hex);
            }
            return hexString.toString();
    
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }
}
