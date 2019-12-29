//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#ifndef UTIL_ARRAYLIST_H
#define UTIL_ARRAYLIST_H

#include <vector>
#include <algorithm>

namespace util{

    template<typename T>
    class ArrayList{
    public:
        ArrayList() = default;

        ArrayList(const ArrayList &list) {
            operator=(list);
        }

        ArrayList(std::initializer_list<T> list){
            operator=(list);
        }

        explicit ArrayList(int size) : vector(size) {}

        T &get(int index) {
            return vector[index];
        }

        const T &get(int index) const {
            return vector[index];
        }

        T &operator[](int index) {
            return vector[index];
        }

        const T &operator[](int index) const {
            return vector[index];
        }

        T *begin() {
            if(size() == 0){
                return nullptr;
            }else{
                return &vector[0];
            }
        }

        T *end() {
            if(size() == 0){
                return nullptr;
            }else{
                return &vector[size()];
            }
        }

        const T *begin() const {
            if(size() == 0){
                return nullptr;
            }else{
                return &vector[0];
            }
        }

        const T *end() const {
            if(size() == 0){
                return nullptr;
            }else{
                return &vector[size()];
            }
        }

        int size() const {
            return vector.size();
        }

        void resize(int newSize) {
            vector.resize(newSize);
        }

        void reserve(int capacity){
            vector.reserve(capacity);
        }

        void clear() {
            vector.clear();
        }

        bool empty() const {
            return size() == 0;
        }

        ArrayList &operator=(const ArrayList &list){
            resize(list.size());
            for(int i = 0; i < list.size();i++){
                get(i) = list.get(i);
            }
            return *this;
        }

        ArrayList &operator=(std::initializer_list<T> list){
            resize(list.size());
            int index = 0;
            for(const T &elm : list){
                get(index++) = elm;
            }
            return *this;
        }

        bool operator==(const ArrayList &list){
            if(size() != list.size()){
                return false;
            }
            for(int i = 0; i < size();i++){
                if(get(i) != list.get(i)){
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const ArrayList &list){
            return !operator==(list);
        }

        T &peek(){
            return get(size() - 1);
        }

        const T &peek() const{
            return get(size() - 1);
        }

        T &add(const T &value) {
            vector.push_back(value);
            return peek();
        }

        T &add() {
            vector.push_back(T());
            return peek();
        }

        T &add(const T &value, int index) {
            vector.insert(vector.begin() + index, value);
            return get(index);
        }

        ArrayList &add(const ArrayList &list){
            for(const T &i : list){
                add(i);
            }
            return *this;
        }

        void remove() {
            vector.pop_back();
        }

        void remove(int index){
            if(index >= 0){
                get(index) = peek();
                remove();
            }
        }

        void removeValue(const T &value){
            remove(find(value));
        }

        void erase(int index) {
            if(index >= 0){
                vector.erase(vector.begin() + index);
            }
        }

        void eraseValue(const T &value){
            erase(find(value));
        }

        void push(const T &value){
            add(value);
        }

        T pop(){
            T t = peek();
            vector.pop_back();
            return t;
        }

        bool contains(const T &value){
            return find(value) != -1;
        }

        int find(const T &value){
            for(int i = 0; i < size();i++){
                if(value == get(i)){
                    return i;
                }
            }
            return -1;
        }

        int indexOf(T &elm){
            return (int)(&elm - begin());
        }

        void swap(ArrayList &list){
            vector.swap(list.vector);
        }

        void sort(){
            std::sort(vector.begin(), vector.end());
        }

        int binaryFind(const T &value){
            int l = 0;
            int r = size() - 1;
            while(r >= l){
                int mid = l + (r - l) / 2;
                if(get(mid) == value){
                    return mid;
                }
                if(get(mid) > value){
                    r = mid - 1;
                }else{
                    l = mid + 1;
                }
            }
            return -1;
        }

    private:
        std::vector<T> vector;
    };

}

#endif //UTIL_ARRAYLIST_H
