#pragma once

#include "Encoder.h"

#include <iostream>
#include <vector>
#include <cassert>

// Test for Example 1
void test_example_1()
{
    const char* buffer = "ABAB""ABAB""ABAB""A";
    std::vector<Code> result = encode(buffer, 0, 0, 7);

    // Expected output for "ABABABABABABA"
    std::vector<Code> expected = {
        {0, 0, 'A'},
        {0, 0, 'B'},
        {2, 7, 'B'},
        {2, 3, 0}
    };

    for (size_t i = 0; i < result.size(); ++i)
    {
        assert(result[i].index == expected[i].index);
        assert(result[i].len == expected[i].len);
        assert(result[i].unmatched == expected[i].unmatched);
    }

    char* decoded = new char[strlen(buffer) + 1];
    memset(decoded, 0, strlen(buffer) + 1);
    decode(decoded, strlen(buffer), result);
    assert(!memcmp(decoded, buffer, strlen(buffer)));
    delete[] decoded;

    std::cout << "Example 1 passed!" << std::endl;
}

// Test for Example 2
void test_example_2()
{
    const char* buffer = "ABCD""ABCD""ABCD""AB";
    std::vector<Code> result = encode(buffer, 0, 0, 7);

    // Expected output for "ABCDABCDABCDAB"
    std::vector<Code> expected = {
        {0, 0, 'A'},
        {0, 0, 'B'},
        {0, 0, 'C'},
        {0, 0, 'D'},
        {4, 7, 'D'},
        {4, 2, 0}
    };

    for (size_t i = 0; i < result.size(); ++i)
    {
        assert(result[i].index == expected[i].index);
        assert(result[i].len == expected[i].len);
        assert(result[i].unmatched == expected[i].unmatched);
    }

    char* decoded = new char[strlen(buffer) + 1];
    memset(decoded, 0, strlen(buffer) + 1);
    decode(decoded, strlen(buffer) + 1, result);
    assert(!strcmp(decoded, buffer));
    delete[] decoded;

    std::cout << "Example 2 passed!" << std::endl;
}

// Test for Example 3
void test_example_3()
{
    const char* buffer = "XYZ""XYZ""XYZ";
    std::vector<Code> result = encode(buffer, 0, 0, 7);

    // Expected output for "XYZXYZXYZ"
    std::vector<Code> expected = {
        {0, 0, 'X'},
        {0, 0, 'Y'},
        {0, 0, 'Z'},
        {3, 6, 0}
    };

    char* decoded = new char[strlen(buffer) + 1];
    memset(decoded, 0, strlen(buffer) + 1);
    decode(decoded, strlen(buffer) + 1, result);
    assert(!strcmp(decoded, buffer));
    delete[] decoded;

    for (size_t i = 0; i < result.size(); ++i)
    {
        assert(result[i].index == expected[i].index);
        assert(result[i].len == expected[i].len);
        assert(result[i].unmatched == expected[i].unmatched);
    }

    std::cout << "Example 3 passed!" << std::endl;
}

// Test for Example 4
void test_example_4()
{
    const char* buffer = "HELLOHELLO";
    std::vector<Code> result = encode(buffer, 0, 0, 7);

    // Expected output for "HELLOHELLO"
    std::vector<Code> expected = {
        {0, 0, 'H'},
        {0, 0, 'E'},
        {0, 0, 'L'},
        {1, 1, 'O'},
        {5, 5, 0}
    };

    for (size_t i = 0; i < result.size(); ++i)
    {
        assert(result[i].index == expected[i].index);
        assert(result[i].len == expected[i].len);
        assert(result[i].unmatched == expected[i].unmatched);
    }

    char* decoded = new char[strlen(buffer) + 1];
    memset(decoded, 0, strlen(buffer) + 1);
    decode(decoded, strlen(buffer) + 1, result);
    assert(!strcmp(decoded, buffer));
    delete[] decoded;

    std::cout << "Example 4 passed!" << std::endl;
}

// Test for Example 5
void test_example_5()
{
    const char* buffer = "AABC""AABC""AAB";
    std::vector<Code> result = encode(buffer, 0, 0, 7);

    // Expected output for "AABCAABCAAB"
    std::vector<Code> expected = {
        {0, 0, 'A'},
        {1, 1, 'B'},
        {0, 0, 'C'},
        {4, 7, 0}
    };

    for (size_t i = 0; i < result.size(); ++i)
    {
        assert(result[i].index == expected[i].index);
        assert(result[i].len == expected[i].len);
        assert(result[i].unmatched == expected[i].unmatched);
    }

    char* decoded = new char[strlen(buffer) + 1];
    memset(decoded, 0, strlen(buffer) + 1);
    decode(decoded, strlen(buffer) + 1, result);
    assert(!strcmp(decoded, buffer));
    delete[] decoded;

    std::cout << "Example 5 passed!" << std::endl;
}

// Test 6: Longer string with no repetitions
void test_example_6()
{
    const char* buffer = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<Code> result = encode(buffer, 0, 0, 7);

    // Expected output for "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    std::vector<Code> expected = {
        {0, 0, 'A'},
        {0, 0, 'B'},
        {0, 0, 'C'},
        {0, 0, 'D'},
        {0, 0, 'E'},
        {0, 0, 'F'},
        {0, 0, 'G'},
        {0, 0, 'H'},
        {0, 0, 'I'},
        {0, 0, 'J'},
        {0, 0, 'K'},
        {0, 0, 'L'},
        {0, 0, 'M'},
        {0, 0, 'N'},
        {0, 0, 'O'},
        {0, 0, 'P'},
        {0, 0, 'Q'},
        {0, 0, 'R'},
        {0, 0, 'S'},
        {0, 0, 'T'},
        {0, 0, 'U'},
        {0, 0, 'V'},
        {0, 0, 'W'},
        {0, 0, 'X'},
        {0, 0, 'Y'},
        {0, 0, 'Z'}
    };

    for (size_t i = 0; i < result.size(); ++i)
    {
        assert(result[i].index == expected[i].index);
        assert(result[i].len == expected[i].len);
        assert(result[i].unmatched == expected[i].unmatched);
    }

    char* decoded = new char[strlen(buffer) + 1];
    memset(decoded, 0, strlen(buffer) + 1);
    decode(decoded, strlen(buffer) + 1, result);
    assert(!strcmp(decoded, buffer));
    delete[] decoded;

    std::cout << "Example 6 passed!" << std::endl;
}

// Test 7: String with the same character repeated
void test_example_7()
{
    const char* buffer = "AAAA""AAAA""AA";  // Repeated 'A' characters
        std::vector<Code> result = encode(buffer, 0, 0, 7);

    // Expected output for "AAAAAAAAAA"
    std::vector<Code> expected = {
        {0, 0, 'A'},
        {1, 7, 'A'},
        {1, 1, 0}
    };

    for (size_t i = 0; i < result.size(); ++i)
    {
        assert(result[i].index == expected[i].index);
        assert(result[i].len == expected[i].len);
        assert(result[i].unmatched == expected[i].unmatched);
    }

    char* decoded = new char[strlen(buffer) + 1];
    memset(decoded, 0, strlen(buffer) + 1);
    decode(decoded, strlen(buffer) + 1, result);
    assert(!strcmp(decoded, buffer));
    delete[] decoded;

    std::cout << "Example 7 passed!" << std::endl;
}

// Test 8: String with fully distinct characters
void test_example_8()
{
    const char* buffer = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";  // All distinct characters
        std::vector<Code> result = encode(buffer, 0, 0, 7);

    // Expected output for "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    std::vector<Code> expected = {
        {0, 0, 'A'},
        {0, 0, 'B'},
        {0, 0, 'C'},
        {0, 0, 'D'},
        {0, 0, 'E'},
        {0, 0, 'F'},
        {0, 0, 'G'},
        {0, 0, 'H'},
        {0, 0, 'I'},
        {0, 0, 'J'},
        {0, 0, 'K'},
        {0, 0, 'L'},
        {0, 0, 'M'},
        {0, 0, 'N'},
        {0, 0, 'O'},
        {0, 0, 'P'},
        {0, 0, 'Q'},
        {0, 0, 'R'},
        {0, 0, 'S'},
        {0, 0, 'T'},
        {0, 0, 'U'},
        {0, 0, 'V'},
        {0, 0, 'W'},
        {0, 0, 'X'},
        {0, 0, 'Y'},
        {0, 0, 'Z'}
    };

    for (size_t i = 0; i < result.size(); ++i)
    {
        assert(result[i].index == expected[i].index);
        assert(result[i].len == expected[i].len);
        assert(result[i].unmatched == expected[i].unmatched);
    }

    char* decoded = new char[strlen(buffer) + 1];
    memset(decoded, 0, strlen(buffer) + 1);
    decode(decoded, strlen(buffer) + 1, result);
    assert(!strcmp(decoded, buffer));
    delete[] decoded;

    std::cout << "Example 8 passed!" << std::endl;
}

// Test 10: String with a single character
void test_example_10()
{
    const char* buffer = "X";  // Single character string
    std::vector<Code> result = encode(buffer, 0, 0, 7);

    // Expected output for "X"
    std::vector<Code> expected = {
        {0, 0, 'X'}
    };

    for (size_t i = 0; i < result.size(); ++i)
    {
        assert(result[i].index == expected[i].index);
        assert(result[i].len == expected[i].len);
        assert(result[i].unmatched == expected[i].unmatched);
    }

    char* decoded = new char[strlen(buffer) + 1];
    memset(decoded, 0, strlen(buffer) + 1);
    decode(decoded, strlen(buffer) + 1, result);
    assert(!strcmp(decoded, buffer));
    delete[] decoded;

    std::cout << "Example 10 passed!" << std::endl;
}

// Test 11: String with a mix of numbers and letters
void test_example_11()
{
    const char* buffer = "A1B2C3""A1B2C3";  // Mixed alphanumeric string
        std::vector<Code> result = encode(buffer, 0, 0, 7);

    // Expected output for "A1B2C3A1B2C3"
    std::vector<Code> expected = {
        {0, 0, 'A'},
        {0, 0, '1'},
        {0, 0, 'B'},
        {0, 0, '2'},
        {0, 0, 'C'},
        {0, 0, '3'},
        {6, 6, 0}
    };

    for (size_t i = 0; i < result.size(); ++i)
    {
        assert(result[i].index == expected[i].index);
        assert(result[i].len == expected[i].len);
        assert(result[i].unmatched == expected[i].unmatched);
    }

    char* decoded = new char[strlen(buffer) + 1];
    memset(decoded, 0, strlen(buffer) + 1);
    decode(decoded, strlen(buffer) + 1, result);
    assert(!strcmp(decoded, buffer));
    delete[] decoded;

    std::cout << "Example 11 passed!" << std::endl;
}

void test_example_12()
{
    // Hardcoded random ASCII string of size 434
    const char* buffer =
        "FsmnD^Tti33hZ4Xc9EoZdHZ6IVsjU9xUoFSfdR9DZs2qsx57TWR1z2gL4gqHdzGFN89vpaV8LgVtxf31H0z1S"
        "Vu08Q6x2Fc@dbV2rx0kb8u5FZl1JReEKbdhL0zFHv5Z78nYhUbJjc0ywzWy9l2K8gg7Gb23zvsZv7fHY0nsLq0V"
        "PzYqx5wB2fbp2tbQF7YX0ykzB6Hg3EvD3VA2SJe5fxK5h1bR5LoeDQDRw5g2h0qJZn3sqSpxd0EX6K6oBy5gS6M"
        "TnXqzq3mkGJ7xO6VzyQdV4y1Mc8i85k8chGp7cb6iWVzmx19e2hf9YszHq9P3sm2bpREz0eq4ftqoaJXfx38vCh"
        "Hl7O7tPZlEFjCUxgeX0KpNrFySpbw5Rba1z5ppTqNk7WL0kHK3c9yHF5PvQsoTkXRs5saxRIUhrzY6pahHqFg70";

    std::vector<Code> result = encode(buffer, 0, 0, 7);

    char* decoded = new char[strlen(buffer) + 1];
    memset(decoded, 0, strlen(buffer) + 1);
    decode(decoded, strlen(buffer), result);
    assert(!strcmp(decoded, buffer));
    delete[] decoded;

    std::cout << "Example 12 passed!" << std::endl;
}

void test_example_13()
{
    // Hardcoded random ASCII string of size ~1200
    const char* buffer =
        "g3sxt9zkl1jo6x0ZxeX6cfUqpa1g2Fb4EZrtpi7KHgYPzrk4vfbdyFjcD5tDhdbrlHT1No3Hpa0NjBpi0lLr9bZy39"
        "Mzr8XOl7qsgFgRp3tE0oOSCuTuz2Rm7Akj6s0A4m6fyX9qdzY9LwDdOzw1DbM6gZtYjCJNmI7wqkL7h0shv06gfFl"
        "8Pfdq7pz1ktX6fl20JjHXTb9lYij0xVrU4PxXh2fCg1Txa6g8Pqgx2KH4x2PUh7x4o41yT0YV1bgNK4jofvpoYbmw"
        "TK7slhqlQreTucEJgggAfq9ktSbuWsHE0pTbGgCUh5rPRyKNF5qxW0b1dJxeqTj16tuTo0T8Xs2OdqsqjlXi05Thn"
        "B0fNffOAxdP9kiz92PzER2yv2vJ53Mv8Y5MXYHbZQ7RpPmn7LPq3auwiXlO2p87tgiPoIMqegJlqlmr2pt2e2DiS7"
        "FsmnD^Tti33hZ4Xc9EoZdHZ6IVsjU9xUoFSfdR9DZs2qsx57TWR1z2gL4gqHdzGFN89vpaV8LgVtxf31H0z1S"
        "Vu08Q6x2Fc@dbV2rx0kb8u5FZl1JReEKbdhL0zFHv5Z78nYhUbJjc0ywzWy9l2K8gg7Gb23zvsZv7fHY0nsLq0V"
        "PzYqx5wB2fbp2tbQF7YX0ykzB6Hg3EvD3VA2SJe5fxK5h1bR5LoeDQDRw5g2h0qJZn3sqSpxd0EX6K6oBy5gS6M"
        "TnXqzq3mkGJ7xO6VzyQdV4y1Mc8i85k8chGp7cb6iWVzmx19e2hf9YszHq9P3sm2bpREz0eq4ftqoaJXfx38vCh"
        "Hl7O7tPZlEFjCUxgeX0KpNrFySpbw5Rba1z5ppTqNk7WL0kHK3c9yHF5PvQsoTkXRs5saxRIUhrzY6pahHqFg70"
        "6K6cfNxZpCjxxkpWcQoP9cK5a8qVqE0Gd6SwTxU1Hmc2uow4PxGv0xXJwjl8SY05l2yLpZOuYglZmjknFdW8MkAmhL"
        "8bgeZyU7K0IQrObhQ67nM4lZ0FfhB61VmnXkvRe08uXqJjhdEjN5dcub8VuBmf6m2WgZyXWg2cOq8pz3lUpNFe9X9"
        "u4fsP5dTuv3sgeUyt6RnmqbhPxuDXlzFrjfby26ahm3b3ICsct98CcnlXK5Ciw7hC9yr8pgVpZmd7oVykOH6f0tvD"
        "8Wh2sfaym9Or2pWVot5PftgN9U6tWRf3k4vL3EnphAqTp92KLfc7CpmcKz9e84Bq68t2be8ChY6jwgTdu1kpLrgl4"
        "uCvNZXrCpHJkX9Ba62YwMmg8hxyT0a4IK6yyYsbnA6LB3qs3wfCbQtfAOVY7YxA2st9JpdyTjv17IScMoTmdWi8Op";

    std::vector<Code> result = encode(buffer, 0, 0, 7);

    char* decoded = new char[strlen(buffer) + 1];
    memset(decoded, 0, strlen(buffer) + 1);
    decode(decoded, strlen(buffer), result);
    assert(!strcmp(decoded, buffer));
    delete[] decoded;

    std::cout << "Example 13 passed!" << std::endl;
}

void test_example_14()
{
    // Hardcoded random ASCII string of size 5000
    const char* buffer =
        "6K6cfNxZpCjxxkpWcQoP9cK5a8qVqE0Gd6SwTxU1Hmc2uow4PxGv0xXJwjl8SY05l2yLpZOuYglZmjknFdW8MkAmhL"
        "8bgeZyU7K0IQrObhQ67nM4lZ0FfhB61VmnXkvRe08uXqJjhdEjN5dcub8VuBmf6m2WgZyXWg2cOq8pz3lUpNFe9X9"
        "u4fsP5dTuv3sgeUyt6RnmqbhPxuDXlzFrjfby26ahm3b3ICsct98CcnlXK5Ciw7hC9yr8pgVpZmd7oVykOH6f0tvD"
        "8Wh2sfaym9Or2pWVot5PftgN9U6tWRf3k4vL3EnphAqTp92KLfc7CpmcKz9e84Bq68t2be8ChY6jwgTdu1kpLrgl4"
        "uCvNZXrCpHJkX9Ba62YwMmg8hxyT0a4IK6yyYsbnA6LB3qs3wfCbQtfAOVY7YxA2st9JpdyTjv17IScMoTmdWi8Op";
    
    std::vector<Code> result = encode(buffer, 0, 0, 7);

    char* decoded = new char[strlen(buffer) + 1];
    memset(decoded, 0, strlen(buffer) + 1);
    decode(decoded, strlen(buffer), result);
    assert(!strcmp(decoded, buffer));
    delete[] decoded;

    std::cout << "Example 14 passed!" << std::endl;
}

void encode_all_tests()
{
    // Test with example strings
    test_example_1();
    test_example_2();
    test_example_3();
    test_example_4();
    test_example_5();
    test_example_6();
    test_example_7();
    test_example_8();
    test_example_10();
    test_example_11();
    test_example_12();
    test_example_13();
    test_example_14();
}

