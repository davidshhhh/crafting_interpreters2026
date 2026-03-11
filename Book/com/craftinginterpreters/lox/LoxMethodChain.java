package Book.com.craftinginterpreters.lox;

import java.util.List;

class LoxMethodChain {
    final List<LoxFunction> chain;
    int index;

    LoxMethodChain(List<LoxFunction> chain) {
        this.chain = chain;
        this.index = 0;
    }

    LoxFunction peek() {
        if (index >= chain.size()) return null;
        return chain.get(index);
    }

    boolean isEmpty() {
        return index >= chain.size();
    }

    void advance() {
        index++;
    }

    void advanceToNext() {
        index++;
    }
}
