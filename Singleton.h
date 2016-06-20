//
// Created by Yorick Rommers on 2016/06/18.
//

#ifndef CV_SOLO_SINGLETON_H
#define CV_SOLO_SINGLETON_H

#include <algorithm>
#include <vector>
class ObjModel;
class Player;

class Singleton{
public:
    static Singleton* Instance();
    std::vector<ObjModel*> models;
    Player *p;
    void DeleteModel(ObjModel* obj);

private:
    Singleton(){};  // Private so that it can  not be called
    Singleton(Singleton const&){};             // copy constructor is private
    Singleton& operator=(Singleton const&){};  // assignment operator is private
    static Singleton* m_pInstance;
};


#endif //CV_SOLO_SINGLETON_H
