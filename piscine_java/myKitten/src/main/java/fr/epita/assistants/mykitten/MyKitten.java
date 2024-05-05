package fr.epita.assistants.mykitten;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Stream;

public class MyKitten {
    /**
     * Initializer.
     *
     * @param srcPath Source file path.
     */
    public MyKitten(String srcPath) {
        try {
            this.streamContent = Files.readAllLines(Paths.get(srcPath)).stream();
        } catch (IOException e) {
            throw new NoClassDefFoundError();
        }
    }

    /**
     * Use the streamContent to replace `wordToReplace` with "miaou". Don't forget
     * to add the line number beforehand for each line. Store the new
     * result directly in the streamContent field.
     *
     * @param wordToReplace The word to replace
     */
    public void replaceByMiaou(String wordToReplace) {
        AtomicInteger cmp = new AtomicInteger(1);
        streamContent = streamContent.map(i -> cmp.getAndIncrement()+ " " + i.replaceAll(wordToReplace, "miaou"));
    }

    /**
     * Use the streamContent to write the content into the destination file.
     *
     * @param destPath Destination file path.
     */
    public void toFile(String destPath) {
        try {
            Files.write(Paths.get(destPath), streamContent.toList(), StandardCharsets.UTF_8);
        } catch (IOException e) {
            throw new NoClassDefFoundError();
        }
    }

    /**
     * Creates an instance of MyKitten and calls the above methods to do it
     * straightforwardly.
     *
     * @param srcPath       Source file path
     * @param destPath      Destination file path
     * @param wordToReplace Word to replace
     */
    public static void miaou(String srcPath, String destPath,
                             String wordToReplace) {
        // FIXME
        MyKitten kiti = new MyKitten(srcPath);
        kiti.replaceByMiaou(wordToReplace);
        kiti.toFile(destPath);
    }

    public Stream<String> streamContent;
}
