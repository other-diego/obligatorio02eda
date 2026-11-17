#include "book.hpp"
#include "catalog.hpp"
#include <iostream>
#include <sstream>

using namespace std;

struct NodoArbol {
    Book* b;
    NodoArbol* izq;
    NodoArbol* der;
};

struct Catalog {
    NodoArbol* raiz;
};

Catalog *catalog_create() {
    Catalog *c = new Catalog;
    c->raiz = nullptr;
    return c;
}

NodoArbol* nodo_create(Book* b) {
    NodoArbol *nuevo_nodo = new NodoArbol;
    nuevo_nodo->b = b;
    nuevo_nodo->der = nullptr;
    nuevo_nodo->izq = nullptr;
    return nuevo_nodo;
}


bool catalog_insert_rec(NodoArbol*& abb, Book* b) {
    if (abb == nullptr)
    {
        abb = nodo_create(b);
        return true;
    } 
    else if (book_code(abb->b) == book_code(b))
    {
        return false;
    }
    else if (book_code(b) < book_code(abb->b) )
    {
        if (abb->izq == nullptr)
        {
            
            abb->izq = nodo_create(b);
            return true;
        }
        else
        {
            return catalog_insert_rec(abb->izq, b);
        }
        
    }
    else
    {
        if (abb->der == nullptr)
        {
            abb->der = nodo_create(b);
            return true;
        }
        else
        {
            return catalog_insert_rec(abb->der, b);
        }
    }   
}

bool catalog_insert(Catalog *c, Book *b) {
    return catalog_insert_rec(c->raiz, b);
} 

Book * catalog_find_rec(const NodoArbol* abb, int code) {
    if (abb == nullptr)
    {
        return nullptr;
    }
    else if (book_code(abb->b) == code)
    {
        return abb->b;
    }
    else if (code < book_code(abb->b))
    {
        return catalog_find_rec(abb->izq, code);
    }
    else 
    {
        return catalog_find_rec(abb->der, code);
    }   
}

Book *catalog_find(const Catalog *c, int code) {
    return catalog_find_rec(c->raiz, code);
} 

NodoArbol* extract_successor(NodoArbol *&abb) {
    if (abb->izq == nullptr)
    {
        NodoArbol* suc = abb;
        abb = abb->der;
        return suc;
    }
    else 
    {
        return extract_successor(abb->izq);
    }
}

bool catalog_remove_rec(NodoArbol *&abb, int code) {
    if (abb == nullptr)
    {
        return false;
    } 
    if (code == book_code(abb->b))
    {
        NodoArbol *aux = abb;
        if (abb->izq != nullptr && abb->der != nullptr)
        {
            NodoArbol* suc = extract_successor(abb->der);
            
            suc->izq = abb->izq;
            suc->der = abb->der;
            abb = suc;
        }
        else if (abb->izq != nullptr)
        {
            abb = abb->izq;
        }
        else {
            abb = abb->der;
        }
        book_destroy(aux->b);
        delete aux;
        return true;
    }
    else if (code < book_code(abb->b))
    {
        return catalog_remove_rec(abb->izq, code);
    }
    else 
    {
        return catalog_remove_rec(abb->der, code);
    }
}

bool catalog_remove(Catalog *c, int code){
    return catalog_remove_rec(c->raiz, code);
} 

void print_book(const Book *b) {
    cout << book_code(b) << " " << book_title(b) << " " << book_author(b) << " " << book_available(b) << "/" << book_total(b) << endl;
}

void catalog_print_rec(const NodoArbol *abb) {
    if (abb != nullptr)
    {
        catalog_print_rec(abb->izq);
        print_book(abb->b);
        catalog_print_rec(abb->der);
    }
}

void catalog_print(const Catalog *c) {
    cout << "CATALOGO:" << endl;
    catalog_print_rec(c->raiz);
}

void print_author(const Book *b, const string &author) {
    if (author.compare(book_author(b)) == 0)
    {
        cout << book_code(b) << " " << book_title(b) << endl;
    }   
}

void catalog_print_author_rec(const NodoArbol *abb, const string &author) {
    if (abb != nullptr)
    {
        catalog_print_author_rec(abb->izq, author);
        print_author(abb->b, author);
        catalog_print_author_rec(abb->der, author);
    }
}

void catalog_print_author(const Catalog *c, const std::string &author) {
    cout << "AUTOR " << author << ":" << endl;
    catalog_print_author_rec(c->raiz, author);
}

int catalog_count_rec(const NodoArbol *abb) {
    if (abb == nullptr)
    {
        return 0;
    }
    
    int count_izq = catalog_count_rec(abb->izq);
    int count_der = catalog_count_rec(abb->der);
    return 1 + count_izq + count_der;
}

int catalog_count(const Catalog *c) {
    return catalog_count_rec(c->raiz);
}

int catalog_height_rec(const NodoArbol *abb) {
    if (abb == nullptr)
    {
        return 0;
    }
    int left_height = catalog_height_rec(abb->izq);
    int right_height = catalog_height_rec(abb->der);
    
    if (left_height > right_height)
    {
        return 1 + left_height;
    }
    else
    {
        return 1 + right_height;
    }  
}

int catalog_height(const Catalog *c) {
    return catalog_height_rec(c->raiz);
}

void catalog_destroy_rec(NodoArbol *abb) {
    if (abb == nullptr)
    {
        return;
    }
    catalog_destroy_rec(abb->izq);
    catalog_destroy_rec(abb->der);
    book_destroy(abb->b);
    delete abb;
}

void catalog_destroy(Catalog *c) {
    catalog_destroy_rec(c->raiz);
    delete c;
} 