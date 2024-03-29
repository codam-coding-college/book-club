package org.example;

public class StringRotation {

    public boolean isRotation(String s1, String s2) {
        if (s1.length() == s2.length()) {
            String concatenated = s1 + s1;
            return concatenated.contains(s2);
        }
        return false;
    }
}
