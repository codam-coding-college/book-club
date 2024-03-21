package org.example;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class IsUniqueTest {

    private static IsUnique isUnique;

    @BeforeAll
    static void setUp() {
        isUnique = new IsUnique();
    }

    @Test
    void uniqueString() {
        assertTrue(isUnique.isUnique("abcdefg"));
    }

    @Test
    void notUniqueString() {
        assertFalse(isUnique.isUnique("hello"));
    }

    @Test
    void emptyString() {
        assertTrue(isUnique.isUnique(""));
    }

    @Test
    void nullString() {
        assertTrue(isUnique.isUnique(null));
    }
}
