#include "Framework.h"

template <>
void check_equal(float a, float b, const char *sa, const char *sb) {
    if (a != b) throw BaseException("%s(%f) != %s(%f)", sa, a, sb, b);
}

template <>
void check_equal<const char *, const char *>(const char *a, const char *b, const char *sa, const char *sb) {
    if (strcmp(a, b) != 0) { throw BaseException("%s(%s) != %s(%s)", sa, a, sb, b); }
}

bool TestRegistry::RunTests(int type) {
    char spinner[5] = "\\|/-";
    size_t i = 0, s = 0;
    size_t spinidx = 0;
    for (std::vector<Test *>::iterator it = tests.begin(); it != tests.end(); ++it) {
        Test *t = *it;
        i++;
        try {
            t->Run();
            s++;
        } catch (std::exception &e) {
            printf("Test failed with exception: %s\n", e.what());
        } catch (int e) {
            printf("Test failed with error code: %d\n", e);
        } catch (...) {
            printf("Test failed with ellipsis-caught error\n");
        }
        printf("%c\r", spinner[spinidx]);
        spinidx = (spinidx + 1) % 4;
    }
    printf("%lu of %lu tests successful\n", s, i);
    return !(s == i);
}


