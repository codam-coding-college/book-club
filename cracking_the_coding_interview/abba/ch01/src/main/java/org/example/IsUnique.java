package org.example;
class IsUnique {
    public boolean isUnique(String str) {
        int bit = 0;

        if (str == null || str.isEmpty()) {
            return true;
        }
        for (int i = 0; i <  str.length(); i++ ) {
            int c = str.charAt(i) - 'a';
            if ((bit & (1 << c)) > 0) {
                return false;
            }
            bit |= (1 << c);
        }
        return true;
    }
}