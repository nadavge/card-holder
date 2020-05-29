class StateMachine;

class State {
public:
    State() : context(nullptr) {}
    State(StateMachine *context): context(context) {}
    int operator=(const State &other) {
        context = other.context;
    }

private:
    StateMachine *context;
};

class StateMachine {
public:
    StateMachine() : states(nullptr) {};
private:
    State *states;
};

class CardHolderSM;

class CardHolderState: public State {
public:
    CardHolderState(CardHolderSM *context) : State(reinterpret_cast<StateMachine*>(context)) {};

private:
    CardHolderSM *context;
};

class CardHolderInitState: public CardHolderState {
public:
    CardHolderInitState(CardHolderSM *context) : CardHolderState(context) {};
};

class CardHolderSM: public StateMachine {
public:
    enum {
        STATE_INIT = 0,
        STATE_POTATO,
        STATE_COUNT
    };

    CardHolderSM();
    int getStateCount();

private:
    State states[STATE_COUNT];
};

CardHolderSM::CardHolderSM() {
    states[STATE_INIT] = CardHolderInitState(this);
}

int CardHolderSM::getStateCount() {
    return sizeof((*this).states) / sizeof((*this).states[0]);
}

CardHolderSM stateMachine;

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.println(stateMachine.getStateCount());
    delay(1000);
}