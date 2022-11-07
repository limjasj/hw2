#include "mydatastore.h"

//constructor
MyDataStore::MyDataStore() 
{

}

/**
  * Adds a product to the data store
  */
void MyDataStore::addProduct(Product* p)
{
  productSet.insert(p);  

  std::set<std::string> productKeywords = p->keywords();
  std::set<std::string>:: iterator it;
  for(it=productKeywords.begin(); it!=productKeywords.end(); ++it)
  {
    if(keywordMap.find(*it) == keywordMap.end())   //if keyword doesn't exists in map
    {
      std::set<Product*> temp;
      keywordMap.insert(make_pair(*it, temp));   //insert pair with it and temp   
    }

      keywordMap[*it].insert(p); //insert Product p into the value's set
    
  }
  //add map that relates keywords to a product
  //key: words, value: set of products
  //add product to the key: word (if it doesnt exist create new key)
}

/**
  * Adds a user to the data store
  */
void MyDataStore::addUser(User* u)
{
  userSet.insert(u);
}

/**
  * Performs a search of products whose keywords match the given "terms"
  *  type 0 = AND search (intersection of results for each term) while
  *  type 1 = OR search (union of results for each term)
  */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  //put terms into a set
  //compare terms and keywordMap, stick it into a set(found)
  //use intersection and union to filter the products that we got from the "found" set
  //put the products into a vector

  std::set<Product*> foundProducts; //set of products, comes from if a term is in keywordMap
  std::set<Product*> addProducts; //the products you want to add, use with intersection and union  
  bool firstIteration=1;
  //create a set to hold product keywords

  //compare terms and keywordMap
  //if a term appears in productKeywords,then we stick all the products in a set
  std::vector<std::string>::iterator it;      
  for(it = terms.begin(); it != terms.end(); ++it) 
  {
    if(keywordMap.find(*it) != keywordMap.end()) //check if term is in keywordMap
    {
      //on the first iteration, we want to put the keywords directly into productKeywords
      //we can't use intersection/union becuase it needs 2 arguments
      if(firstIteration)
      {
        foundProducts=keywordMap[*it]; //add the set of products(for the word) to set
        firstIteration=0;
      }
      else 
      {
        //go through each product in the set within keywordMap
        //add products into addProducts        
        if (type==0)
        {
          foundProducts = setIntersection(foundProducts, keywordMap[*it]);  
          //find intersection between the keywords in the new product and the established
        }
        else if (type==1)
        {
          foundProducts = setUnion(foundProducts, keywordMap[*it]); 
          //find union between the keywords in the new product and the established
        }
      }
    }
  }

  std::vector<Product*> returnProducts(foundProducts.begin(), foundProducts.end()); //the vector that function will return
  return returnProducts;

}

/**
  * Reproduce the database file from the current Products and User values
  */
void MyDataStore::dump(std::ostream& ofile)
{
  ofile << "<products> \n";

  if(!productSet.empty())
  {
    for(std::set<Product*>::iterator it = productSet.begin(); 
        it != productSet.end(); ++it)  
    {
      (*it)->dump(ofile);     //iterate through productSet and dump each Product (virtual??)
      delete *it;
    }
  }
  
  ofile << "</products> \n" ;

  ofile << "<users> \n" ;
  
  if(!userSet.empty())
  {          
    for(std::set<User*>::iterator it2 = userSet.begin(); 
      it2 != userSet.end(); ++it2)
    {
      (*it2)->dump(ofile);      //iterate through userSet and dump each User
      delete *it2;
    }
  }
  
  ofile << "</users> \n" ;

}

//add to cart, uses hit index
void MyDataStore::addToCart(std::string username, Product* newProduct)
{  
  //1st step: make sure username matches with a user in set userSet
  User* currentUser;  //create User pointer
  std::set<User*>:: iterator it;  //iterate through set userSet to find user
  for(it=userSet.begin(); it!=userSet.end(); it++)
  {
    if(username == (*it)->getName())  //if string username matches a name from userSet
    {
      currentUser=*it;  //set the currentUser to *it, we will use that to push a product
      break;  //break bc we found the user
    }
  }
  
  if(userCart.find(currentUser) == userCart.end())   //if user doesn't exist in map userCart
  {
    std::deque<Product*> temp;
    temp.push_back(newProduct);     //put newProduct into the deque of products
    userCart.insert(make_pair(currentUser, temp));   //insert pair with username and temp   
  }
  else //if user does exist in map userCart
  {
    userCart[currentUser].push_back(newProduct); //insert newProduct into the username's set
  } 
}

//view cart 
std::vector<Product*> MyDataStore::viewCart(std::string username)
{
  //print items in username's cart, with acending index number
  //1st step: make sure username matches with a user in set userSet
  User* currentUser;  //create User pointer
  std::set<User*>:: iterator it;  //iterate through set userSet to find user
  for(it = userSet.begin(); it!=userSet.end(); ++it)
  {
    if(username== (*it)->getName())  //if string username matches a name from userSet
    {
      currentUser=*it;  //set the currentUser to *it, we will use that to push a product
      break;  //break bc we found the user
    }
  }
  //now user is found in userSet

  //create deque of Products to iterate through, from currentUser
  //iterate through currentUser's products, dump products 
  std::vector<Product*> displayVector;
  std::deque<Product*> currentUserProducts=userCart[currentUser];  
  std::deque<Product*>:: iterator it2;
  for(it2 = currentUserProducts.begin(); it2 != currentUserProducts.end(); ++it2)
  {
    //push into vector
    displayVector.push_back(*it2);
  }
  
  return displayVector;
  //userCart[currentUser].displayProducts(displayVector); //call displayProducts function
}

//buy cart
void MyDataStore::buyCart(std::string username)
{
  //1st step: make sure username matches with a user in set userSet
  User* currentUser;  //create User pointer
  std::set<User*>:: iterator it;  //iterate through set userSet to find user
  for(it = userSet.begin(); it!=userSet.end(); it++)
  {
    if(username== (*it)->getName())  //if string username matches a name from userSet
    {
      currentUser=*it;  //set the currentUser to *it, we will use that to push a product
      break;  //break bc we found the user
    }
  }
  
  //iterate in the order added
  std::deque<Product*> temp=userCart[currentUser]; //temp is the deque of the currentUser
  std::deque<Product*>:: iterator it2;  //iterate over temp, contains Products
  for(it2 = temp.begin(); it2!=temp.end(); it2++)
  {
    //if item is in stock & user has enough money
    if(((*it2)->getQty()>=1) && ((currentUser->getBalance())>=((*it2)->getPrice()))) 
    {
      temp.pop_front(); //remove Product from temp deque
      (*it2)->subtractQty(1);    //decrement stock quantity of Product by 1
      currentUser->deductAmount((*it2)->getPrice());  //product price debited from user's credit
      userCart[currentUser]=temp;  //update deque in userCart for currentUser
    }
    // if item not in stock OR user doesn't have enough credit
    // then leave in cart, go to next product
    
  }
}

bool MyDataStore::userExists(std::string username)
{
  bool userDoesExist=0;

  User* currentUser;  //create User pointer
  std::set<User*>:: iterator it;  //iterate through set userSet to find user
  for(it = userSet.begin(); it!=userSet.end(); ++it)
  {
    if(username== (*it)->getName())  //if string username matches a name from userSet
    {
      currentUser=*it;  //set the currentUser to *it, we will use that to push a product
      userDoesExist=1;
      break;  //break bc we found the user
    }
  }
  //now user is found in userSet

  return userDoesExist;
}