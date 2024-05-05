package fr.epita.assistants.embedfiles;

import java.io.*;
import java.util.Optional;
import java.util.stream.Collectors;

public class DisplayEmbedFile {
    private final String filename;

    public DisplayEmbedFile(String filename) {
        this.filename = filename;
    }

    public Optional<String> display() {
        if(filename == null)
            return Optional.empty();
        InputStream inputStream = ClassLoader.getSystemResourceAsStream(filename);
        if (inputStream == null)
            return Optional.empty();
        StringBuilder string = new StringBuilder();

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream)))
        {
            String value;
            while ((value = reader.readLine()) != null)
            {
               string.append(value).append(System.lineSeparator());
            }


        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return Optional.of(string.toString());
    }
}
