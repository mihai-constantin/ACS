package ro.pub.cs.systems.eim.lab07.earthquakelister.general;

public interface Constants {

    final public static boolean DEBUG = true;

    final public static String TAG = "[Earthquake Lister]";

    final public static String EARTHQUAKE_LISTER_WEB_SERVICE_INTERNET_ADDRESS = "http://api.geonames.org/earthquakesJSON?";

    final public static String MISSING_INFORMATION_ERROR_MESSAGE = "All fields need to be completed!";

    final public static String NORTH = "north=";
    final public static String SOUTH = "south=";
    final public static String EAST = "east=";
    final public static String WEST = "west=";
    final public static int NORTH_INDEX = 0;
    final public static int SOUTH_INDEX = 1;
    final public static int EAST_INDEX = 2;
    final public static int WEST_INDEX = 3;
    final public static String CREDENTIALS = "username=eim2017";

    final public static String EARTHQUAKES = "earthquakes";
    final public static String LATITUDE = "lat";
    final public static String LONGITUDE = "lng";
    final public static String MAGNITUDE = "magnitude";
    final public static String DEPTH = "depth";
    final public static String SOURCE = "src";
    final public static String DATE_AND_TIME = "datetime";

}
