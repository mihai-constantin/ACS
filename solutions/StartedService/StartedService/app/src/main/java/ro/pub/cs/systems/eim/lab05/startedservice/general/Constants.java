package ro.pub.cs.systems.eim.lab05.startedservice.general;

import java.util.ArrayList;
import java.util.Arrays;

public interface Constants {

    final public static String TAG = "[Started Service]";

    final public static String ACTION_STRING = "ro.pub.cs.systems.eim.lab05.startedservice.string";
    final public static String ACTION_INTEGER = "ro.pub.cs.systems.eim.lab05.startedservice.integer";
    final public static String ACTION_ARRAY_LIST = "ro.pub.cs.systems.eim.lab05.startedservice.arraylist";

    final public static int MESSAGE_STRING = 1;
    final public static int MESSAGE_INTEGER = 2;
    final public static int MESSAGE_ARRAY_LIST = 3;

    final public static String DATA = "ro.pub.cs.systems.eim.lab05.startedservice.data";

    final public static String STRING_DATA = "EIM";
    final public static int INTEGER_DATA = 2017;
    final public static ArrayList<String> ARRAY_LIST_DATA = new ArrayList<>(Arrays.asList("EIM", "2017"));

    final public static long SLEEP_TIME = 5000;

}
