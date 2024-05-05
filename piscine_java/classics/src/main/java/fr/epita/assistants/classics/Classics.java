package fr.epita.assistants.classics;

import java.util.Arrays;

public class Classics {
    /**
     * Computes the factorial of n.
     *
     * @param n the nth value to compute, negative values should return -1
     * @return the long value of n!
     */
    public static long factorial(int n) {
        if (n < 0)
            return -1;
        if (n == 0)
            return 1;
        else
            return n * factorial(n - 1);
    }

    /**
     * Computes the nth value of the tribonacci suite.
     * f(0) = 0, f(1) = 1, f(2) = 1, f(n+3) = f(n) + f(n+1) + f(n+2)
     *
     * @param n the nth sequence to compute
     */
    public static long tribonacci(int n) {
        if (n < 0)
            return -1;
        long u0 = 0;
        long u1 = 1;
        long u2 = 1;
        long un = 0;
        for (long i = 0; i < n; i++) {
            un = u0 + u1 + u2;
            u0 = u1;
            u1 = u2;
            u2 = un;
        }
        return u0;
    }

    /**
     * Checks if a word is a palindrome.
     *
     * @param word the string to check
     * @return true if the word is a palindrome, false otherwise.
     */
    public static boolean isPalindrome(String word) {
        return word != null && word.replaceAll(" ", "").compareToIgnoreCase(new StringBuilder(word.replaceAll(" ", "")).reverse().toString()) == 0;
    }
      /*Sorts an array using an insertion sort.

      @param array the array to sort in place
     */

    public static void insertionSort(int[] array) {
        int size = array.length;
        for (int i = 1; i < size; i++) {
            int val = array[i];
            int j = i - 1;

            while (j >= 0 && array[j] > val) {
                array[j + 1] = array[j];
                j = j - 1;
            }
            array[j + 1] = val;
        }
    }

    /**
     * Combines two strings by alternating their characters. Must use a StringBuilder.
     * If the strings do not have the same length, appends the remaining characters at the end of the result.
     * For instance, combine("abc", "def") returns "adbecf"
     */
    public static String combine(String a, String b) {
        int size_min = Math.min(a.length(), b.length());
        int size_max = Math.max(a.length(), b.length());
        StringBuilder str = new StringBuilder();
        for (int i = 0; i < size_min; i++) {
            str.append(a.charAt(i));
            str.append(b.charAt(i));
        }
        if (a.length() == size_max)
            str.append(a, size_min, size_max);
        else
            str.append(b, size_min, size_max);
        return str.toString();
    }
}



