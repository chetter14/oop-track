#ifndef NATIVE_DICTIONARY_H
#define NATIVE_DICTIONARY_H

#include <string>

template <typename T>
class NativeDictionary {
 protected:
  // конструктор
  // постусловие: создан пустой словарь
  NativeDictionary() = default;

 public:
  virtual ~NativeDictionary() = default;

  // команды

  // предусловие: такой ключ не существует в словаре
  // постусловие: пара ключ-значение добавлена в словарь
  virtual void put(const std::string& key, T value) = 0;

  // запросы

  virtual bool is_key(
      const std::string& key) = 0;  // содержится ли ключ key в словаре

  // предусловие: в словаре имеется значение по ключу key
  virtual T get(const std::string& key) = 0;

  // запросы статусов (возможные значения статусов)

  virtual int
  get_put_status() = 0;  // успешно; такой ключ уже есть в словаре, значение перезаписано
  virtual int get_get_status() = 0;  // успешно; такого ключа нет в словаре
};

#endif  // NATIVE_DICTIONARY_H
