package org.example;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class CheckPermutationTest {
    private static CheckPermutation permutation;

    @BeforeAll
    static void setUp() {
        permutation = new CheckPermutation();
    }
    @Test
    void sameLengthPermutation() {
        String str1 = "abc";
        String str2 = "bca";
        assertTrue(permutation.isPermutation(str1, str2));
    }

    @Test
    void differentLengthStrings() {
        String str1 = "abc";
        String str2 = "abcd";
        assertFalse(permutation.isPermutation(str1, str2));
    }

    @Test
    void notPermutation() {
        String str1 = "abc";
        String str2 = "def";
        assertFalse(permutation.isPermutation(str1, str2));
    }

    @Test
    void emptyStrings() {
        String str1 = "";
        String str2 = "";
        assertTrue(permutation.isPermutation(str1, str2));
    }

    @Test
    void nullStrings() {
        String str1 = null;
        String str2 = null;
        assertTrue(permutation.isPermutation(str1, str2));
    }
}
