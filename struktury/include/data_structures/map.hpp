#ifndef MAP_HPP_
#define MAP_HPP_


int hash(const std::string& str)
{
  int result = 0;
  for(int i=0; i < str.size(); i++)
  {
    result += static_cast<int>(str[i])*i;
  }

  return result % 1000;
}

template <typename KeyType, typename ValueType>
class Map
{
public:
  Map() {}
  Map(const Map& otherMap) { }

  void insert(const KeyType& key ,const ValueType& value);
  ValueType& operator[](const KeyType& key);
  void remove(const KeyType& key);

private:
  std::array<ValueType, 1000> tab;
};


template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
  int index = hash(key);
  tab[index] = value;
}

template <typename KeyType, typename ValueType>
ValueType &Map<KeyType, ValueType>::operator[](const KeyType &key)
{
  static ValueType value;

  value = tab[hash(key)];

  return value;
}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::remove(const KeyType &key)
{
  tab[hash(key)] = 0;
}

#endif /* MAP_HPP_ */
