class DeallocationTracker {
private:
  bool* reference;

public:
  DeallocationTracker() {
    this->reference = new bool(false);
  }

  ~DeallocationTracker() {
    *this->reference = true;
  }

  bool* getReference() {
    return this->reference;
  }
};
