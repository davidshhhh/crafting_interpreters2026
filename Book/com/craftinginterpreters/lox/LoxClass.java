package Book.com.craftinginterpreters.lox;

/* 
import java.util.List;
import java.util.Map;

class LoxClass implements LoxCallable {
  final String name;
  final LoxClass superclass;

  private final Map<String, LoxFunction> methods;

  LoxClass(String name, LoxClass superclass,
           Map<String, LoxFunction> methods) {
    this.superclass = superclass;
    this.methods = methods;
  }

  LoxFunction findMethod(String name) {
    if (methods.containsKey(name)) {
      return methods.get(name);
    }

    if (superclass != null) {
      return superclass.findMethod(name);
    }

    return null;
  }

  @Override
  public String toString() {
    return name;
  }


  @Override
  public Object call(Interpreter interpreter,
                     List<Object> arguments) {
    LoxInstance instance = new LoxInstance(this);
    LoxFunction initializer = findMethod("init");
    if (initializer != null) {
      initializer.bind(instance).call(interpreter, arguments);
    }
    return instance;
  }

  @Override
  public int arity() {
    LoxFunction initializer = findMethod("init");
    if (initializer == null) return 0;
    return initializer.arity();
  }
}

*/

import java.util.List;
import java.util.Map;
import java.util.HashMap;

class LoxClass implements LoxCallable {
  final String name;
  final LoxClass superclass;

  private final Map<String, LoxFunction> methods;
  private final Map<String, LoxFunction> extensionMethods = new HashMap<>();


  LoxClass(String name, LoxClass superclass, LoxClass metaclass,
           Map<String, LoxFunction> methods) {
    super(metaclass);
    this.superclass = superclass;

    this.name = name;
    this.methods = methods;
  }

  LoxFunction findMethod(String name) {
    if (methods.containsKey(name)) {
      return methods.get(name);
    }

    // Check extension methods
    if (extensionMethods.containsKey(name)) {
      return extensionMethods.get(name);
    }

    if (superclass != null) {
      return superclass.findMethod(name);
    }


    return null;
  }

  void addExtension(String name, LoxFunction method) {
    extensionMethods.put(name, method);
  }


  @Override
  public String toString() {
    return name;
  }

  @Override
  public Object call(Interpreter interpreter,
                     List<Object> arguments) {
    LoxInstance instance = new LoxInstance(this);

    LoxFunction initializer = findMethod("init");
    if (initializer != null) {
      initializer.bind(instance).call(interpreter, arguments);
    }


    return instance;
  }

  @Override
  public int arity() {

    LoxFunction initializer = findMethod("init");
    if (initializer == null) return 0;
    return initializer.arity();

  }

}
