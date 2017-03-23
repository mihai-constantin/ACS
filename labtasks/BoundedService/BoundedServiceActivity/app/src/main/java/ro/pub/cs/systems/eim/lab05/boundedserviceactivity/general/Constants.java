package ro.pub.cs.systems.eim.lab05.boundedserviceactivity.general;

import java.util.ArrayList;
import java.util.Arrays;

public interface Constants {

    final public static String TAG = "[Bounded Service]";

    final public static ArrayList<String> MESSAGES = new ArrayList<>(Arrays.asList("EIM", "2017"));

    final public static int SERVICE_STATUS_UNBOUND = 0;
    final public static int SERVICE_STATUS_BOUND = 1;

}
