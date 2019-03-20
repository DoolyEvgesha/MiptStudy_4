#include "dictionary.h"
#include "gtest/gtest.h"

namespace {
    TEST(push, PushTest){
        char * w1 = "one";
        char * w2 = "two";
        char * w3 = "three";
        dict_fn * d = dict_create();
        dict(d->dct, w1);
        dict(d->dct, w2);
        dict(d->dct, w3);
        EXPECT_EQ(d, 3);
    }
}//namespace
