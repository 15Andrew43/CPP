#include "string.h"

#include <cassert>

void TestCOW() {
    String str1;
    str1.PushBack('a');

    auto p1 = &str1.Get(0);

    {
        String str2(str1);
        assert(&str2.Get(0) == p1);

        str2.PushBack('b');
        assert(&str2.Get(0) != p1);
        assert(str2.Get(0) == 'a');
    }

    {
        String str3(str1);
        str3.Set(0, 'b');
        auto p2 = &str3.Get(0);
        assert(p2 != p1);

        str3.Set(0, 'c');
        assert(p2 == &str3.Get(0));
    }

    {
        String str4;
        str4.PushBack('b');
        str4.PushBack('c');
        String str5(str4);

        str4 = str1;
        assert(str4.Get(0) == 'a');
        assert(&str4.Get(0) == p1);
        assert(str5.Get(0) == 'b');
        assert(str5.Get(1) == 'c');
    }

    {
        String str5(str1);

        assert(&str5.Get(0) == p1);

        assert(str5.Size() == 1);
        assert(&str5.Get(0) == p1);
    }  
}

int main() {
    TestCOW();
    // YOUR TESTS
    return 0;
}
