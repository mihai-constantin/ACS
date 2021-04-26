package ro.pub.cs.systems.eim.lab07.landmarklister.general;

public interface Constants {

    final public static boolean DEBUG = true;

    final public static String TAG = "[Landmark Lister]";

    final public static String LANDMARK_LISTER_WEB_SERVICE_INTERNET_ADDRESS = "http://api.geonames.org/citiesJSON?";

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

    final public static String GEONAMES = "geonames";
    final public static String LATITUDE = "lat";
    final public static String LONGITUDE = "lng";
    final public static String TOPONYM_NAME = "toponymName";
    final public static String POPULATION = "population";
    final public static String CODE_NAME = "fcodeName";
    final public static String NAME = "name";
    final public static String WIKIPEDIA_WEB_PAGE_ADDRESS = "wikipedia";
    final public static String COUNTRY_CODE = "countrycode";

}
