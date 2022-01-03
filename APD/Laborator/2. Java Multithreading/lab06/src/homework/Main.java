package homework;

public class Main {

    public static int binary_search(int[] v, int x){
        int m;
        int i = 0;
        int j = v.length - 1;

        while(i <= j) {
            m = (j - i) / 2 + i;
            if(v[m] == x) {
                return m;
            }

            if(v[m] < x) {
                i = m + 1;
            }
            else {
                j = m - 1;
            }
        }

        return -1;
    }

    public static void main(String[] args) {

        int n = 5;
        int[] v = {0, 1, 2, 3, 4};

        System.out.println(binary_search(v, 0));
        System.out.println(binary_search(v, 1));
        System.out.println(binary_search(v, 2));
        System.out.println(binary_search(v, 3));
        System.out.println(binary_search(v, 4));
        System.out.println(binary_search(v, 5));
    }
}
