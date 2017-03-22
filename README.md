# Dissecting-MFC
When I was a new guy to learn MFC, I read the book called Dissecting MFC. I like it very much. The author presents the basic principles about how to design and implement MFC mechanisms like ``Dynamic Create``, ``Runtime Type Identification``, ``Message Mapping``, ``Command Routing`` and ``Persistence``.

To be honest, I am deeply impressed by its simplicity and clearity. In MFC, the ``Macors`` of C++ functions like a magical dragon. Usually very simple sentence like ``IMPLEMENT_DYNAMIC(CCmdTarget, CObject)`` may involves a bundle of c++ codes.

## Compile and Run
This program is compiled and run in visual studio 2008. It contains 6 projects. Some simple ``makefile``s are also added to it, which resides in the corresponds project directory. 

## Brief introduction of MFC main features

### Runtime Type Identification
Wow, don't you think it wonderful to recognize what kind of the object is?  You can call a method such as ``object.isKindOf`` to judge the object type in runtime rather than compiling time.

### Dynamic Create
It means that you can create the objects dynamicly rather than by hard coding. What you need to do is to provide a class name, and the magic will happen by returning you a corresponding ``CRuntimeClass`` object. You can simply call ``runtimeClass->CreateObject`` to create the object with the given name.
``CRuntimeClass`` is a static class object for every MFC class who need to be instanced. 

### Message Mapping and Command Routing
These two mechanisms worked togather. ``Message Mapping`` is used to bind command id with the processing function so that if one object receives a command, it will trigger the binded function. ``Command Routing`` direct the flow of this command id among serveral MFC objects. When one command comes to one object without binded function, it will be transfered to another up-level MFC object until it is accurately processed or digested by final default function. 


