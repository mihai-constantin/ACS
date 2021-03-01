package Implementations;

import java.io.IOException;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.ArrayList;

import static java.nio.file.FileVisitResult.CONTINUE;

/**
 * Retine caile tuturor fisierelor Java din directorul dat.
 */
public class FilesCounter extends SimpleFileVisitor<Path> {

    private ArrayList<Path> javaFiles;

    public final ArrayList<Path> getJavaFiles() {
        return javaFiles;
    }

    @Override
    public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) {

        if (file.toString().endsWith(".class")) {
            System.out.format("%s%n", file);
        }

        return CONTINUE;

    }

    public static void main(String[] args) throws IOException {

        Path currentDirectory = Paths.get("").toAbsolutePath();
        FilesCounter filesCounter = new FilesCounter();
        Files.walkFileTree(currentDirectory, filesCounter);
    }
}
