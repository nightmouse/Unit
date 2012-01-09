#include <vector>
#include <string>

#include "Basic/src/rc_ptr.h"
#include "Harness/src/ITest.h"
#include "Harness/src/TestRegistry.h"
#include "Harness/src/TestUtils.h"
#include <iostream>

using namespace std;
using namespace Unit;

namespace  {

class Foo
{
    public:
        void bar() { } 
};



class RC_Ptr_Test: public ITest
{
    public:
        void run();
        string getName() const { return "Self/RC_Ptr"; }
};

static bool _register_ = TestRegistry::Register(new RC_Ptr_Test);

void RC_Ptr_Test::run()
{
    { // make sure an expception is thrown when dereferencing a null pointer
        BEGIN_EXPECTED_EXCEPTION_CHECK("operator-> should have thrown an exception and did not!");
        rc_ptr<Foo>p;
        p->bar();
        END_EXPECTED_EXCEPTION_CHECK();
    }

    {   // check basic functionality
        rc_ptr<Foo> t1(new Foo);
        t1.set(new Foo);
    }

    {   // check basic functionality
        rc_ptr<Foo> t1(new Foo);
        rc_ptr<Foo> t2 = t1;
    }

    { // check the assignment operator
        rc_ptr<Foo> t1(new Foo);
        rc_ptr<Foo> t2 = t1;
        if (t1 != t2) { 
            fail("assignment operator does not work correctly");
        }
    }

    { // check that the assignment operator works on null pointers
        rc_ptr<Foo> t1;
        rc_ptr<Foo> t2 = t1;
        if (t1 != t2) { 
            fail("assignment operator failed null pointer copy");
        }
    }


    {  // test equality operatory
        rc_ptr<Foo> t1(new Foo);
        rc_ptr<Foo> t2;
        if (t1 == t2)  { 
            fail("equality operator should have returned false");
        }
    }

    { // check null pointers throw exceptions via operator *
        BEGIN_EXPECTED_EXCEPTION_CHECK("operator * should have thrown an exception and did not!");
        rc_ptr<Foo> t1;
        *t1;
        END_EXPECTED_EXCEPTION_CHECK();
    }

    {    // make sure it works well with stl
        typedef rc_ptr<class Foo> Ptr;
        typedef vector<Ptr> VectorType;
        Ptr p(new Foo);       // +1
        VectorType test;
        test.push_back(p);   // +1     
        test.push_back(p);   // +1
        test.push_back(p);   // +1
        test.push_back(p);   // +1 = 5
        if (p.getRefCount() != 5) { 
            fail("did not get the correct reference count.");
        }
    }

} // end Run


} // end namespace
