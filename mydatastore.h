#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "util.h"
#include "datastore.h"


class MyDataStore : public DataStore{
  public:
    //constructor
    MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    //add to cart, uses hit index
    void addToCart(std::string username, Product* newProduct);

    //view cart 
    std::vector<Product*> viewCart(std::string username);

    //buy cart
    void buyCart(std::string username);

  private:
  //set of products
    std::set<Product*> productSet;
    std::map<std::string, std::set<Product*>> keywordMap;
    std::set<User*> userSet;
    std::map<User*, std::deque<Product*>> userCart;
};
#endif