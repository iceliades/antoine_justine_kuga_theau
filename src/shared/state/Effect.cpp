#include "Effect.h"

using namespace std;
using namespace state;

Effect::Effect() {
    Disarmed = false;
    Immobilised = false;
    Stunned = false;
}

Effect::~Effect() {

}

//------------------------------------------------- Setters ------------------------------------------------------------
void Effect::setImmobilised(bool i) {
    Immobilised = i;
}

void Effect::setDisarmed(bool d) {
    Disarmed = d;
}

void Effect::setStunned(bool s) {
    Stunned = s;
}

//------------------------------------------------- Getters ------------------------------------------------------------
bool Effect::getImmobilised() {
    return Immobilised;
}

bool Effect::getDisarmed() {
    return Disarmed;
}

bool Effect::getStunned() {
    return Stunned;
}
