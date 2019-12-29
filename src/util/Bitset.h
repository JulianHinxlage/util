//
// Copyright (c) 2019 Julian Hinxlage. All rights reserved.
//

#ifndef UTIL_BITSET_H
#define UTIL_BITSET_H

namespace util{

    template<int bits>
    class Bitset{
    public:
        static const int bytes = ((bits - 1) / 8) + 1;
        unsigned char data[bytes];

        Bitset() : data() {}

        Bitset(const Bitset &bitset) : data() {
            operator=(bitset);
        }

        void reset(){
            for(int i = 0; i < bytes;i++){
                data[i] = 0;
            }
        }

        bool get(int index) const {
            return data[index / 8] >> (index % 8) & 1u;
        }

        bool set(int index, bool value = true){
            if(value){
                data[index / 8] |= (1u << (unsigned)(index % 8));
            }else{
                data[index / 8] &= (~(1u << (unsigned)(index % 8)));
            }
            return value;
        }

        bool all(const Bitset &bitset) const {
            for(int i = 0; i < bytes; i++){
                if((data[i] & bitset.data[i]) != bitset.data[i]){
                    return false;
                }
            }
            return true;
        }

        bool any(const Bitset &bitset) const {
            for(int i = 0; i < bytes; i++){
                if((data[i] & bitset.data[i]) != 0u){
                    return true;
                }
            }
            return false;
        }

        bool operator==(const Bitset &bitset){
            for(int i = 0; i < bytes;i++){
                if(data[i] != bitset.data[i]){
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const Bitset &bitset) const {
            return !operator==(bitset);
        }

        Bitset &operator=(const Bitset &bitset){
            for(int i = 0; i < bytes;i++){
                data[i] = bitset.data[i];
            }
            return *this;
        }
    };

}

#endif //UTIL_BITSET_H
