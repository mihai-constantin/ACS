package ro.pub.cs.systems.eim.lab06.pheasantgame.general;

import android.os.AsyncTask;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.List;
import java.util.concurrent.ExecutionException;

import ro.pub.cs.systems.eim.lab06.pheasantgame.network.WordFinderService;

public class Utilities {

    public static List<String> getWordListStartingWith(String prefix) {
        AsyncTask<String, Object, List<String>> wordFinderService = new WordFinderService().execute(prefix);
        try {
            return wordFinderService.get();
        } catch (InterruptedException interruptedException) {
            Log.d(Constants.TAG, "An exception has occurred " + interruptedException.getMessage());
            if (Constants.DEBUG) {
                interruptedException.printStackTrace();
            }
        } catch (ExecutionException executionException) {
            Log.d(Constants.TAG, "An exception has occurred " + executionException.getMessage());
            if (Constants.DEBUG) {
                executionException.printStackTrace();
            }
        }
        return null;
    }

    public static boolean wordValidation(String word) {
        return !getWordListStartingWith(word).isEmpty();
    }

    public static BufferedReader getReader(Socket socket) throws IOException {
        return new BufferedReader(new InputStreamReader(socket.getInputStream()));
    }

    public static PrintWriter getWriter(Socket socket) throws IOException {
        return new PrintWriter(socket.getOutputStream(), true);
    }

}
