#ifndef MAP_HPP_
#define MAP_HPP_

template <typename KeyType, typename ValueType>
class Map
{
public:
  Map() {}
  Map(const Map& otherMap) { }

  void insert(const KeyType& key ,const ValueType& value);
  ValueType& operator[](const KeyType& key);
  void remove(const KeyType& key);
};


template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
  // TODO: implement
}

template <typename KeyType, typename ValueType>
ValueType &Map<KeyType, ValueType>::operator[](const KeyType &key) {

  // TODO: implement
  static ValueType value;
  return value;

}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::remove(const KeyType &key)
    {

  // TODO: implement
    }

#endif /* MAP_HPP_ */
