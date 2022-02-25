#ifndef CALLBACK_H
#define CALLBACK_H
#include <vector>
/**
* @author Juliver Ybarsabal
* @date 27/05/2021
* @brief The callback class is used to collect data when passed as a
function parameter.
*/
template<class T>
class callback
{
private:
    /** Holds collected data */
    static vector<T> dataVector;
public:
    /**
    * @brief Adds data to vector.
    *
    * @param T &data
    * @return static void
    */
    static void GetData(T &data)
    {
        dataVector.push_back(data);
    }
    /**
    * @brief returns size of vector.
    *
    * @return int
    */
    int size();
    /**
    * @brief Clears the vector.
    *
    * @return void
    */
    void clear();
    /**
    * @brief Overloads operator to allow access to vector elements directly.
    *
    * @param int index
    * @return T&
    */
    T& operator[](int index);
};
template<class T>
int callback<T>::size()
{
    return dataVector.size();
}
template<class T>
void callback<T>::clear()
{
    dataVector.clear();
}
template<class T>
T& callback<T>::operator[](int index)
{
    if(index < dataVector.size())
    {
        return dataVector.at(index);
    }
    else
    {
        return *(new T); //memory leak!
    }
}
template<class T>
vector<T> callback<T>::dataVector;
#endif // callback
