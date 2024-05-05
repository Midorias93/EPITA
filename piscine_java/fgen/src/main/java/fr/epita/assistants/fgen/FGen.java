package fr.epita.assistants.fgen;

import java.io.File;
import java.io.IOException;
import java.net.URISyntaxException;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;


public class FGen {
    enum opcode {
        CREATE, CHANGE, DELETE
    }

    ;
    List<String> Lines;
    String path;

    public FGen(final String inputPath) {

        URL resource = this.getClass().getClassLoader().getResource(inputPath);
        assert resource != null;
        try {
            this.Lines = Files.readAllLines(Path.of(resource.toURI()));
        } catch (IOException | URISyntaxException e) {
            throw new RuntimeException(e);
        }
        this.path = new File("").getAbsolutePath();
        execLines();
    }

    public void execLines() {
        if (Lines != null) {
            for (int i = 0; i < Lines.size(); i++) {
                if (Lines.get(i).startsWith("+") && Lines.get(i).endsWith("/")) creatDir(Lines.get(i));
                if (Lines.get(i).startsWith("+") && !Lines.get(i).endsWith("/")) creatFile(Lines.get(i));
                if (Lines.get(i).startsWith(">")) move(Lines.get(i));
                if (Lines.get(i).startsWith("-")) delete(Lines.get(i));
            }
        }


    }

    public void creatDir(String line) {
        new File(this.path + File.separator + line.substring(2)).mkdirs();

    }

    public void creatFile(String line) {
        if (line.contains("/"))
            new File(this.path + File.separator + line.substring(2, line.lastIndexOf("/"))).mkdirs();

        try {
            new File(this.path + File.separator + line.substring(2)).createNewFile();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public void move(String line) {
        if (line.startsWith("/")) {
            if (!new File(line.substring(2)).isDirectory())
                throw new RuntimeException("existe pas");
            else
                this.path = line.substring(2);
        }
        if (!new File(path + File.separator + line.substring(2)).isDirectory())
            throw new RuntimeException("existe pas");
        else
            this.path = this.path + File.separator + line.substring(2);
    }

    public void delDir(File file) {
        File[] contents = file.listFiles();
        if (contents != null) {
            for (File f : contents) {
                delDir(f);
            }
        }
        file.delete();
    }

    public void delete(String line) {
        File file = new File(path + File.separator + line.substring(2));
        delDir(file);
    }
}
