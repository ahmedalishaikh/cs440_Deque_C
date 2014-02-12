#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <iostream>
#include "Deque.hpp"

// May assume memcpy()-able.
// May assume = operator.

struct YourClass {
    int id;
    char name[10];
};

bool
YourClass_less_by_id(const YourClass &o1, const YourClass &o2) {
    return o1.id < o2.id;
}

void
YourClass_print(const YourClass *o) {
    printf("%d\n", o->id);
    printf("%s\n", o->name);
}

Deque_DEFINE(YourClass)

int
main() {

    Deque_YourClass deq;
    Deque_YourClass_ctor(&deq, YourClass_less_by_id);

    assert(deq.size(&deq) == 0);
    assert(deq.empty(&deq));

    // Should print "---- Deque_YourClass, 14".
    // printf("---- %s, %zu\n", deq.type_name, sizeof(deq.type_name));
    std::cout << "---- " << deq.type_name << ", " << sizeof(deq.type_name) << std::endl;

    deq.push_back(&deq, YourClass{1, "Joe"});
    deq.push_back(&deq, YourClass{2, "Mary"});
    deq.push_back(&deq, YourClass{3, "Tom"});
    deq.push_front(&deq, YourClass{0, "Mike"});
    deq.push_front(&deq, YourClass{-1, "Mary"});

    YourClass_print(&deq.front(&deq));
    YourClass_print(&deq.back(&deq));
    assert(deq.front(&deq).id == -1);
    assert(deq.back(&deq).id == 3);

    deq.pop_front(&deq);
    deq.pop_back(&deq);
    assert(deq.front(&deq).id == 0);
    assert(deq.back(&deq).id == 2);

    assert(deq.size(&deq) == 3);

    for (Deque_YourClass_Iterator it = deq.begin(&deq); !Deque_YourClass_Iterator_equal(it, deq.end(&deq)); it.inc(&it)) {
        YourClass_print(&it.deref(&it));
    }

    // Test decrement.
    {
        auto it = deq.end(&deq);
        it.dec(&it);
        assert(it.deref(&it).id == 2);
    }

    printf("Using at.\n");

    for (size_t i = 0; i < 3; i++) {
        YourClass_print(&deq.at(&deq, i));
    }

    deq.clear(&deq);

    deq.dtor(&deq);

    // Test equality.  It is undefined behavior if the two deques were constructed with different
    // comparison functions.
    {
        Deque_YourClass deq1, deq2;
        Deque_YourClass_ctor(&deq1, YourClass_less_by_id);
        Deque_YourClass_ctor(&deq2, YourClass_less_by_id);

        deq1.push_back(&deq1, YourClass{1, "Joe"});
        deq1.push_back(&deq1, YourClass{2, "Jane"});
        deq1.push_back(&deq1, YourClass{3, "Mary"});
        deq2.push_back(&deq2, YourClass{1, "Joe"});
        deq2.push_back(&deq2, YourClass{2, "Jane"});
        deq2.push_back(&deq2, YourClass{3, "Mary"});

        assert(Deque_YourClass_equal(deq1, deq2));

        deq1.pop_back(&deq1);
        deq1.push_back(&deq1, YourClass{4, "Mary"});
        assert(!Deque_YourClass_equal(deq1, deq2));

        deq1.dtor(&deq1);
        deq2.dtor(&deq2);
    }
}
