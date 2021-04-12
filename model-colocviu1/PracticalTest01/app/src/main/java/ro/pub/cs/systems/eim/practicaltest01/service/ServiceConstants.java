package ro.pub.cs.systems.eim.practicaltest01.service;

import android.icu.text.SimpleDateFormat;
import android.icu.util.Calendar;

public class ServiceConstants {

    final public static String TAG = "[Started Service]";

    final public static String ACTION_STRING = "ro.pub.cs.systems.eim.practicaltest01.service.string";
    final public static String ACTION_INTEGER = "ro.pub.cs.systems.eim.practicaltest01.service.integer";
    final public static String ACTION_MG = "ro.pub.cs.systems.eim.practicaltest01.service.mg";

    final public static int MESSAGE_STRING = 1;
    final public static int MESSAGE_INTEGER = 2;
    final public static int MESSAGE_MG = 3;

    final public static String DATA = "ro.pub.cs.systems.eim.practicaltest01.service.data";

    final public static int INTEGER_DATA = Integer.parseInt(new SimpleDateFormat("yyyy").format(Calendar.getInstance().getTime()));

    final public static long SLEEP_TIME = 10000;

    final public static String DEBUG = "DEBUG";

}