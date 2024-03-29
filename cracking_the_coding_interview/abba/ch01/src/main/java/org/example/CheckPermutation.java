package org.example;

public class CheckPermutation {
    public boolean isPermutation(String str1, String str2) {
        if (str1 == null && str2 == null) {
            return true;
        }

        if (str1.length() != str2.length()) {
            return false;
        }


        int[] charCount = new int[128];

        // Increment count for each character in str1
        for (int i = 0; i < str1.length(); i++) {
            charCount[str1.charAt(i)]++;
        }

        for (int i = 0; i < str2.length(); i++) {
            charCount[str2.charAt(i)]--;
            if (charCount[str2.charAt(i)] < 0) {
                return false;
            }
        }
        return true;
    }
}
