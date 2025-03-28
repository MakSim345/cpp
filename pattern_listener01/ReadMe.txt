Simple C++ code implementing pattern "Listener":
    - with detailed explanation 
    - and CMake file

Each listener has a name, which is specified in the constructor, and the update method will prepend the name to the message.


Explanation

1. Subject Class:
        This class maintains a list of listeners and has methods to attach listeners and notify them of events.
        attach(Listener* listener): Adds a listener to the list.
        notify(const std::string& message): Calls the update method on each attached listener, passing the message.

2. Listener Interface:
        This is an abstract class defining the update method that all concrete listeners must implement.

3. ConcreteListener Class:
        Implements the Listener interface and defines how to respond to notifications by overriding the update method.

4. Main Function:
        Creates a Subject and two ConcreteListener instances.
        Attaches the listeners to the subject.
        Sends a notification message to all attached listeners.
