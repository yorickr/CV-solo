//
// Created by Yorick Rommers on 2016/06/18.
//

#include "Singleton.h"
#include <stddef.h>  // defines NULL

// Global static pointer used to ensure a single instance of the class.
Singleton* Singleton::m_pInstance = NULL;

/** This function is called to create an instance of the class. 
    Calling the constructor publicly is not allowed. The constructor 
    is private and is only called by this Instance function.
*/

Singleton* Singleton::Instance() {
    if (!m_pInstance)   // Only allow one instance of class to be generated.
        m_pInstance = new Singleton;

    return m_pInstance;
}

void Singleton::DeleteModel(ObjModel * model) {

    models.erase(std::remove(models.begin(), models.end(), model), models.end());

}


