ZLang
=====

A plugin framework for preprocessor DSLs in C/C++. 

Synopsis
--------

One problem with macros is that they invade the global namespace, and if we are not careful can inadvertently replace an unrelated token. For example, if we were to define a `greet` macro like this:

    #define greet(x) Hello x

Perhaps, another developer unaware of our `greet` macro decides to add a `greet` function:

    // This won't compile since the following line expands to:
    //
    //     void hello const char * msg
    // 
    // Which is not correct C/C++.
    //
    void greet(const char * msg)
    {
        ...
    }

And if you aren't using gcc or clang, the developer will most likely be left with confusion why this fails with a compile error. So, in general, we use a convention such that our macro must is written with all caps, like this:

    #define GREET(x) Hello x

Well this is starting to look ugly, but it helps a little, until we decide to use LibAmigo and it defines another `GREET` macro like this:

    #define GREET(x) Hola x

Uh-oh, now we have two different behaviors depending on what files we include. This is could get suprising, so we decide to prefix all our macros with a unique namespace like `FOO` for example:

    #define FOO_GREET(x) Hello x

Now, its gotten even uglier. Well ZLang can help solve these problems without uglifying macros like this.

Usage
-----

Lets start with our greeting macros:

    FOO_GREET(world) // Expands to Hello world

ZLang provides a way to call this macro, like this:

    $(greet world) // Expands to Hello world

or fully qualified like this:

    $(foo_greet world) // Expands to Hello world

It uses the `$` as the entry point. If this can't be used(on a few legacy platforms the `$` is not supported), the `ZLANG` macro can be used instead:

    ZLANG(greet world) // Expands to Hello world

To plug our `FOO_GREET` macro into ZLang we have to register it first. This is done by defining a macro by appending our name to the `ZLANG_` macro and then defining it to our macro with parenthesis around it, like this:

    // Notice the space between the macro name and the parenthesis.
    #define ZLANG_foo_greet (FOO_GREET)

This will let us now use our macro like this:

    $(foo_greet world) // Expands to Hello world

This is the fully qualified name, we can define `ZLANG_NS` to `foo`(perhaps during the build with `-DZLANG_NS=foo`), so we can now use:

    $(greet world) // Expands to Hello world

Up to 8 namespaces can be specified, and it will search through them until it can find a matching name. It does this by prepending the name to the name given by the user. So say, `ZLANG_NS` was defined to `bar,foo` it will first see if `bar_greet` is valid and then it will try `foo_greet`, which is valid.

Additionally, the `ZLANG_NS` can be overridden locally. This can be useful for libraries writers who want to define namespaces without overriding the user defined namespaces. To override, just define `ZLANG_USE` at the top of the file, and undefine it at the end of the file, like this for using namespace `bar` and `foo`:

    #define ZLANG_USE (bar,foo)

    $(greet world)

    #undef ZLANG_USE

The `ZLANG_USE` macro does require parenthesis around the namespace definitions. 

Requirements
------------

This has been tested on gcc, clang, and msvc preprocessors. ZLang is one header, and has no dependencies. Also, to register macros does not require the ZLang header. Its only required for usage. This can allow a library to optionally register macros with ZLang, without needing a ZLang dependency.
