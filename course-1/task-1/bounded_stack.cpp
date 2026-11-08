template <typename T>
class BoundedStack {
 public:
  // Тип для статуса запроса pop() для отличия от обычных целочисленных значений - int.
  enum class POP_STATUS {
    NIL = 0, // команда pop() ещё не вызывалась с момента создания или вызова clear()
    OK,      // последний pop() отработал нормально
    ERR      // на стеке ничего нет
  };

  // Тип для статуса запроса push() для отличия от обычных целочисленных значений - int.
  enum class PUSH_STATUS {
    NIL = 0, // команда push() ещё не вызывалась с момента создания или вызова clear()
    OK,      // последний push() отработал нормально
    ERR      // на стеке нет места для нового элемента
  };

  // Тип для статуса запроса peek() для отличия от обычных целочисленных значений - int.
  enum class PEEK_STATUS {
    NIL = 0, // команда peek() ещё не вызывалась с момента создания или вызова clear()
    OK,      // последний peek() отработал нормально
    ERR      // на стеке ничего нет
  };

 public:
  // предусловие: значение аргумента capacity должно быть положительным целочисленным числом
  // постусловие: пустой инициализированный стек, с которым можно работать
  explicit BoundedStack(int capacity = 32) : capacity_(capacity) {
    clear();
  }

  // следуем Rule-Of-Five:

  // копирование стека недоступно 
  BoundedStack(const BoundedStack<T>&) = delete;
  BoundedStack<T>& operator=(const BoundedStack<T>&) = delete;

  // перемещение стека доступно
  BoundedStack(BoundedStack<T>&&) = default;
  BoundedStack<T>& operator=(BoundedStack<T>&&) = default;

  ~BoundedStack() = default;

  // предусловие: в стеке есть место для нового элемента
  // постусловие: в стек добавлено новое значение
  void push(T value) {
    if (size() < capacity_) {
      bounded_stack_.Append(value);
      push_status_ = PUSH_STATUS::OK;
    } else {
      push_status_ = PUSH_STATUS::ERR;
    }
  }

  // предусловие: стек не пустой
  // постусловие: из стека удалён верхний элемент
  void pop() {
    if (size() > 0) {
      bounded_stack_.RemoveAt(-1);
      pop_status_ = POP_STATUS::OK;
    } else {
      pop_status_ = POP_STATUS::ERR;
    }
  }

  // постусловие: стек очищается, все статусы выставляются в изначальное состояние
  void clear() {
    // пустой список/стек
    bounded_stack_ = {};

    // начальные статусы для предусловий peek(), pop() и push()
    peek_status_ = PEEK_STATUS::NIL;
    pop_status_ = POP_STATUS::NIL;
    push_status_ = PUSH_STATUS::NIL;
  }

  // предусловие: стек не пустой
  T peek() {
    T result;
    if (size() > 0) {
      result = bounded_stack_[-1];
      peek_status_ = PEEK_STATUS::OK;
    } else {
      result = 0;
      peek_status_ = PEEK_STATUS::ERR;
    }
    return result;
  }

  int size() const { return bounded_stack_.Length(); }

  // запросы статусов
  POP_STATUS get_pop_status() const noexcept { return pop_status_; }
  PEEK_STATUS get_peek_status() const noexcept { return peek_status_; }
  PUSH_STATUS get_push_status() const noexcept { return push_status_; }

 private:
  List<T> bounded_stack_;  // основное хранилище стека
  int capacity_;           // максимально допустимое кол-во элементов в стеке

  PEEK_STATUS peek_status_;  // статус запроса peek()
  POP_STATUS pop_status_;    // статус команды pop()
  PUSH_STATUS push_status_;  // статус команды push()
};
