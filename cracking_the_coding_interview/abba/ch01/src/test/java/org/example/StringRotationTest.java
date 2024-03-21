package org.example;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class StringRotationTest {

    private static StringRotation rotation;

    @BeforeAll
    static void setUp() {
        rotation = new StringRotation();
    }

    @Test
    void rotation() {
        String s1 = "waterbottle";
        String s2 = "erbottlewat";
        assertTrue(rotation.isRotation(s1, s2));
    }

    @Test
    void notRotation() {
        String s1 = "hello";
        String s2 = "world";
        assertFalse(rotation.isRotation(s1, s2));
    }
}