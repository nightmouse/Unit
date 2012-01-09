#ifndef _rc_ptr_h_
#define _rc_ptr_h_

// -----------------------------------------------------------------------
// reference counted smart pointer, not thread safe
// see shared_ptr for a thread safe smart pointer
// -----------------------------------------------------------------------

#include "Basic/src/NPE.h"

namespace Unit
{

template <typename T>
class rc_ptr
{
    public:
        // default constructor
        rc_ptr():
            ptr_m(0),
            ref_m()
            { }

        // pointer constructor
        rc_ptr(T * ptr): 
            ptr_m(ptr),
            ref_m()
        { 
            ref_m.increment();
        }

        // copy constructor
        rc_ptr(rc_ptr<T> & tmp): 
            ptr_m(tmp.ptr_m),
            ref_m(tmp.ref_m)
        { 
            ref_m.increment();
        }

        // copy constructor - note the const
        rc_ptr(const rc_ptr<T> & tmp): 
            ptr_m(tmp.ptr_m),
            ref_m(tmp.ref_m)
        { 
            ref_m.increment();
        }

        // destructor
        ~rc_ptr() throw()
        {
            if (!ref_m.decrement()) { 
                delete ptr_m;
                ptr_m = 0;
            }
        }

        // operator ==
        // returns true if both rc_ptr's refer to the same
        // address in memory
        bool operator==(const rc_ptr<T> & rhs) const throw()
        { 
            if (!ptr_m && !rhs.ptr_m) { 
                return true;
            } else if ((!ptr_m && rhs.ptr_m) || (ptr_m && !rhs.ptr_m)) { 
                return false;
            }

            return &(*ptr_m) == &(*rhs.ptr_m);
        }

        // operator !=
        // returns false if neither pointer has the same address
        bool operator!=(const rc_ptr<T> & rhs) const throw()
        {
            if (!ptr_m && !rhs.ptr_m) { 
                return false;
            } else if ((!ptr_m && rhs.ptr_m) || (ptr_m && !rhs.ptr_m)) { 
                return true;
            }

            return &(*ptr_m) != &(*rhs.ptr_m);
        }

        // operator =
        rc_ptr<T> & operator=(const rc_ptr<T> & rhs) throw ()
        {
            if (!ref_m.decrement()) { 
                delete ptr_m;
            }

            ptr_m = rhs.ptr_m;
            ref_m = rhs.ref_m;
            ref_m.increment();
            return *this;
        }

        // operator =
        rc_ptr<T> & operator=(T * rhs) throw ()
        {
            if (!ref_m.decrement()) { 
                delete ptr_m;
            }

            ptr_m = rhs;
            ref_m.increment();
            return *this;
        }
        
        // operator *
        T & operator*() const 
        {
            if (!ptr_m) { throw NullPointerException(); }
            return *ptr_m;
        }

        // operator ->
        T * operator->() const 
        {
            if (!ptr_m) { throw NullPointerException(); }
            return ptr_m;
        }

        T * get() const throw()
        {
            return ptr_m;
        }

        void set(T * ptr) throw()
        {
            ref_m.reset();
            delete ptr_m;
            ptr_m = ptr;
            ref_m.increment();
        }

        unsigned getRefCount() const throw()
        {
            return ref_m.get();
        }

    private:

        class Ref
        {
            public:
                Ref(): count_m(NULL) { } 

                void increment() 
                { 
                    if (!count_m) { 
                        count_m = new int;
                    }
                    ++(*count_m);
                }

                int decrement() 
                { 
                    if (!count_m) { 
                        return 0;
                    }
                    --(*count_m);
                    if (*count_m == 0) { 
                        delete count_m;
                        count_m = NULL;
                        return 0;
                    }
                    return *count_m;
                }

                void reset()
                {
                    if (count_m) { 
                        --(*count_m);
                        if (*count_m == 0) { 
                            delete count_m;
                        }
                    }
                    // if this function is called count_m needs to become null so that it can be re-allocated by increment
                    count_m = NULL; 
                }

                int get() const 
                {
                    if (!count_m) { 
                        return 0;
                    }
                    return *count_m;
                }

            private:
                int * count_m;
        }; // end class

        Ref ref_m;
        T * ptr_m;

}; // end class

} // end namespace

#endif

